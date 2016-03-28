//
//  enum_def.h
//  camelUpPredictor
//
//  Created by Donald Jones on 28/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#ifndef enum_def_h
#define enum_def_h

#undef ENUM_START
#undef ENUM_ADD
#undef ENUM_END
#define ENUM_START(NAME) enum NAME {
#define ENUM_ADD(NAME, VALUE) NAME = VALUE,
#define ENUM_END(NAME) COUNT_##NAME };

#endif /* enum_def_h */
