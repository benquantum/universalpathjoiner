#pragma region Universal Path Joiner
//DO NOT call "pathJoinStr" (not recommended) 
#include <string>
inline std::string pathJoinStr(const std::string& p) {
    return p;
}
template<typename... Args>
std::string pathJoinStr(const std::string& p1, const std::string& p2, Args... args) {
    char sep = '/';
#ifdef _WIN32
    sep = '\\';
#endif
    std::string tmp = p1;
    if (!tmp.empty() && tmp.back() != sep) {
        tmp += sep;
    }
    std::string p2mod = p2;
    if (!p2mod.empty() && p2mod.front() == sep) {
        p2mod = p2mod.substr(1);
    }
    tmp += p2mod;
    return pathJoinStr(tmp, args...);
}
//"pathJoin" wrapper function
template<typename... Args>
const char* pathJoin(const std::string& p1, const std::string& p2, Args... args) {
    static std::string tmp;
    tmp = pathJoinStr(p1, p2, args...);
    return tmp.c_str();
}
//EXAMPLE CALL: pathJoin("assets", "3D", "Chewbacca", "chewie.png")
//For root files, DO NOT use the function, just call "file.png"
#pragma endregion
