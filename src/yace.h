#pragma once

#ifdef _DEBUG
#define LOG( ... ) printf( __VA_ARGS__ )
#else
#define LOG( ... )
#endif
