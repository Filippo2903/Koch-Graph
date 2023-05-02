#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "{ ";
    for (int i = 0; i < vec.size(); i++) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
    }
    os << " }";
    return os;
}

template <typename T>
std::vector<T> operator+(const std::vector<T>& vec0, const std::vector<T>& vec1) {
    std::vector<T> result = vec0;
    result.insert(result.end(), vec1.begin(), vec1.end());
    return result;
}

template <typename T>
std::vector<T>& operator+=(std::vector<T>& result, const std::vector<T>& vec) {
    result.insert(result.end(), vec.begin(), vec.end());
    return result;
}

template <typename T>
bool operator==(const std::vector<T>& vec0, const std::vector<T>& vec1) {
    if (vec0.size() != vec1.size()) return false;
    for (int i = 0; i < vec0.size(); i++) {
        if (vec0[i] != vec1[i])
            return false;
    }
    return true;
}
