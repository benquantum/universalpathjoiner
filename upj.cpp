#pragma region Universal Path Joiner
//Example usage: pathJoin("assets","chewbacca","chewie.png")
#include <cstring>
#include <cstdlib>
#ifdef _WIN32
constexpr char SEP = '\\';
#else
constexpr char SEP = '/';
#endif
inline void appendPart(char* buffer, size_t& len, const char* part) {
    if (!part || !*part) return;
    if (len > 0 && buffer[len - 1] != SEP)
        buffer[len++] = SEP, buffer[len] = '\0';
    if (part[0] == SEP)
        part++;
    while (*part)
        buffer[len++] = *part++;
    buffer[len] = '\0';
}
struct Path {
    char* cstr;
    Path(char* ptr) : cstr(ptr) {}
    ~Path() { std::free(cstr); }

    const char* get() const { return cstr; }
    operator const char*() const { return cstr; }
};
template<typename... Args>
Path pathJoin(const char* first, Args... args) {
    size_t totalLen = std::strlen(first);
    const char* parts[] = {args...};
    for (const char* p : parts)
        totalLen += std::strlen(p) + 1;
    char* buffer = (char*)std::malloc(totalLen + 1);
    if (!buffer) return Path(nullptr);
    size_t len = 0;
    appendPart(buffer, len, first);
    for (const char* p : parts)
        appendPart(buffer, len, p);
    return Path(buffer);
}
#pragma endregion
