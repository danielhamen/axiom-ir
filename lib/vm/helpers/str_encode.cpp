#include <string>

/**
 * Encodes a string into a literal form, escaping special characters
 * e.g. str_encode("hello\nworld") becomes "hello\\nworld"
 */
void str_encode(std::string& str) {
    std::string result;
    result.reserve(str.size() + 10); // reserve slightly more to avoid reallocations

    for (char ch : str) {
        switch (ch) {
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            case '\\': result += "\\\\"; break;
            case '"':  result += "\\\""; break;
            case '\'': result += "\\\'"; break;
            case '\0': result += "\\0"; break;
            default:
                // Only encode visible ASCII (printable characters)
                result += ch;
                break;
        }
    }

    str = std::move('"' + result + '"');
}
