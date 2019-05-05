#pragma once

#ifdef GAMECOMMON_EXPORTS
#define GAMECOMMON_API __declspec(dllexport)
#else
#define GAMECOMMON_API __declspec(dllimport)
#endif // !GAMECOMMON_EXPORTS