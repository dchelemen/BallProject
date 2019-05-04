#pragma once

#ifdef GAMEVIEW_EXPORTS
#define GAMEVIEW_API __declspec(dllexport)
#else
#define GAMEVIEW_API __declspec(dllimport)
#endif // !GAMEVIEW_EXPORTS
