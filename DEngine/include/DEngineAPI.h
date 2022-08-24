#pragma once
#ifdef _DLL

#define DEAPI __declspec(dllexport)

#else

#define DEAPI __declspec(dllimport)

#endif