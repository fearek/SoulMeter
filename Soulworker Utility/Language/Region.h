#pragma once
// SERVER_KOREA : Stove (KR server)
// SERVER_SETAM : Steam (EN, TC Server)
// Supported Languages : _LANG_KOREAN, _LANG_ENGLISH, _LANG_CHINESES
#define SERVER_STEAM
#define _LANG_CHINESES

#ifdef _LANG_KOREAN
#include "Korean.h"
#endif
#ifdef _LANG_ENGLISH
#include "English.h"
#endif
#ifdef _LANG_CHINESES
#include "Chineses.h"
#endif