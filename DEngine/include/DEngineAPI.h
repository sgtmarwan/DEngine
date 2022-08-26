#pragma once
#ifdef _WINDLL

#define DEAPI __declspec(dllexport)

#else

#define DEAPI __declspec(dllimport)

#endif