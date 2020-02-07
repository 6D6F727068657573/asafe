#include <regex>
#include <vector>

#include "types.h"

#ifndef PARSER_H
#define PARSER_H

namespace arch_safeguard {

struct announcement {
    url link;
    timestamp date;
    std::string subject;

    announcement(url&& link, timestamp&& date, std::string&& subject);

    std::string str() const;
};

std::vector<announcement> parse_announcements(const std::string& arch_announce_mail);

url arch_announce_url(timestamp date);

} // arch_safeguard
#endif // PARSER_H
