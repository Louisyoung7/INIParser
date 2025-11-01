#include "value.h"

namespace louis {
namespace value {
// 基本数据类型转Value
Value::Value(int value) {
    *this = value;
}
Value::Value(double value) {
    *this = value;
}
Value::Value(const char* value) {
    *this = value;
}
Value::Value(const string& value) {
    *this = value;
}
Value::Value(bool value) {
    *this = value;
}

// 重载赋值运算符
Value& Value::operator=(int value) {
    stringstream ss;
    ss << value;
    value_ = ss.str();
    return *this;
}
Value& Value::operator=(double value) {
    stringstream ss;
    ss << value;
    value_ = ss.str();
    return *this;
}
Value& Value::operator=(const char* value) {
    value_ = value;
    return *this;
}
Value& Value::operator=(const string& value) {
    value_ = value;
    return *this;
}
Value& Value::operator=(bool value) {
    value_ = value ? "true" : "false";
    return *this;
}

// Value转基本数据类型
Value::operator int() const {
    return std::atoi(value_.c_str());
}
Value::operator double() const {
    return std::atof(value_.c_str());
}
Value::operator string() const {
    return value_;
}
Value::operator bool() const{
    return value_ == "true";
}

}  // namespace value
}  // namespace louis