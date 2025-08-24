#pragma region Universal Path Joiner
#include <cstring>
#include <cstddef>
#ifdef _WIN32
constexpr char SEP = '\\';
#else
constexpr char SEP = '/';
#endif
struct Path {
    static constexpr size_t MAX_LEN = 256;
    char buffer[MAX_LEN] = {0};
};
inline void appendPart(char* buffer, size_t maxLen, const char* part) {
    if (!part || !*part) return;
    size_t len = std::strlen(buffer);
    if (len > 0 && buffer[len - 1] != SEP) buffer[len++] = SEP;
    while (*part == SEP) part++;
    while (*part && len < maxLen - 1) {
        if (*part == SEP && len > 0 && buffer[len - 1] == SEP) { ++part; continue; }
        buffer[len++] = *part++;
    }
    buffer[len] = '\0';
}
template<typename... Args>
const char* pathJoin(const char* first, Args... args) {
    static Path pool[1024];
    static size_t index = 0;
    Path* p = &pool[index];
    index = (index + 1) % 1024;
    p->buffer[0] = '\0';
    appendPart(p->buffer, Path::MAX_LEN, first);
    const char* parts[] = { args... };
    for (const char* part : parts) appendPart(p->buffer, Path::MAX_LEN, part);
    return p->buffer;
}
#pragma endregion
