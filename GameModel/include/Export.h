#pragma once

#ifdef GAMEMODEL_EXPORTS
#define GAMEMODEL_API __declspec(dllexport)
#else
#define GAMEMODEL_API __declspec(dllimport)
#endif // !GAMEMODEL_EXPORTS