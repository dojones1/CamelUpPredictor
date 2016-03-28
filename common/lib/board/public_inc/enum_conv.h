//
//  enum_conv.h
//  camelUpPredictor
//
//  Created by Donald Jones on 28/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#undef ENUM_START
#undef ENUM_ADD
#undef ENUM_END
#if 0
##define ENUM_START(NAME) const char *NAME_to_string(NAME val) { switch (val) {
##define ENUM_ADD(NAME, VALUE) case NAME: return #NAME;
##define ENUM_END(NAME) default: return "Invalid value"; } }
#endif
/*
std::ostream& operator<<(std::ostream& os, enum Colours c)
{
    if (c >= ColoursCount || c < 0) return os << "???";
    return os << colours_str[c];
}
*/

#define ENUM_START(NAME) char const* const str_##NAME[] = {
#define ENUM_ADD(NAME, VALUE) #NAME,
#define ENUM_END(NAME) }; \
ostream& operator<<(ostream& os, enum NAME c) \
{ \
    if (c >= COUNT_##NAME || c < 0) return os << "???"; \
    return os << str_##NAME[c]; \
} \
