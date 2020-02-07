#include <array>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <string_view>

#include "utils.h"
#include "announce.h"
#include "settings.h"

namespace arch_safeguard {

announcement::announcement(url&& link, timestamp&& date, std::string&& subject)
    : link(link), date(date), subject(subject) { }

std::string announcement::str() const {
    auto time = std::chrono::system_clock::to_time_t(date);
    auto sstream = std::stringstream();
    sstream << std::put_time(gmtime(&time), settings::arch_announce_date_format())
            << ": " << subject << "\n"
            << "[" << link << "]";
    return sstream.str();
}

struct announcement_collector {
    url link;
    timestamp date;
    std::string subject;
    std::vector<announcement> announcements;

    void push_announcement() {
        announcements.emplace(announcements.begin(), std::move(link), std::move(date), std::move(subject));
    }
};

struct line_processor {
    const std::string title;
    mutable announcement_collector* collector_ptr;

    line_processor(std::string title, announcement_collector* collector_ptr)
        : title(std::move(title)), collector_ptr(collector_ptr) {}

    virtual void assign_value(std::string_view value) const = 0;

    bool process_line(std::string_view line) const {
        if(line.find(title.c_str()) == 0) {
            auto content = line.substr(title.length());
            assign_value(trim(content));
            return true;
        }
        return false;
    }
};

struct date_line_processor : public line_processor {

    date_line_processor(announcement_collector* collector_ptr) : line_processor("Date:", collector_ptr) {}

    void assign_value(std::string_view value) const override {
        std::tm tm = {};
        strptime(value.data(), settings::arch_announce_date_format(), &tm);
        collector_ptr->date = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }
};

struct subject_line_processor : public line_processor {

    subject_line_processor(announcement_collector* collector_ptr) : line_processor("Subject: [arch-announce]", collector_ptr) {}

    void assign_value(std::string_view value) const override {
        collector_ptr->subject = value;
    }
};

struct url_line_processor : public line_processor {

    url_line_processor(announcement_collector* collector_ptr) : line_processor("URL:", collector_ptr) {}

    void assign_value(std::string_view value) const override {
        collector_ptr->link = value;
    }
};

template<class... LineProcessor>
constexpr std::tuple<LineProcessor ...> create_processors(announcement_collector* collector) {
    return std::make_tuple<LineProcessor ...>(LineProcessor(collector) ...);
}

template<class... LineProcessor>
class aggregated_line_processor {
    size_t state_id;
    announcement_collector collector;
    std::tuple<LineProcessor ...> processors;
    std::array<const line_processor*, sizeof... (LineProcessor)> states;

public:
    aggregated_line_processor()
        : state_id(0),
          collector(announcement_collector()),
          processors(create_processors<LineProcessor...>(&collector)),
          states(pointer_array<line_processor, decltype(processors)>(processors)) {}

    void process_line(std::string_view line) {
        if(states[state_id]->process_line(line)) {
            ++state_id;
            if(state_id == states.size()) {
                collector.push_announcement();
                state_id = 0;
            }
        }
    }

    std::vector<announcement> finish() {
        auto announcements = collector.announcements;
        std::sort(announcements.begin(), announcements.end(), [](auto& first, auto& second) {
            return first.date > second.date;
        });
        return announcements;
    }
};

std::vector<announcement> parse_announcements(const std::string& arch_announce_mail) {
    auto processor = aggregated_line_processor<date_line_processor, subject_line_processor, url_line_processor>();

    auto line_begin_index = 0ul;
    while(line_begin_index < arch_announce_mail.size()) {
        auto line_end_index = arch_announce_mail.find('\n', line_begin_index);
        if(line_end_index == std::string::npos) {
            line_end_index = arch_announce_mail.size();
        }

        if(line_end_index > line_begin_index) {
            auto line_begin = &arch_announce_mail[line_begin_index];
            auto line = std::string_view(line_begin, line_end_index - line_begin_index);
            processor.process_line(line);
        }

        line_begin_index = line_end_index + 1;
    }

    return processor.finish();
}

url arch_announce_url(timestamp date) {
    auto time = std::chrono::system_clock::to_time_t(date);
    auto sstream = std::stringstream();
    sstream << std::put_time(localtime(&time), settings::arch_announce_url_format());
    return sstream.str();
}

} // arch_safeguard
