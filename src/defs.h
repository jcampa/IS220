#pragma once

#if __cplusplus > 199711L
	#define MOVE(a) std::move(a)
	#define CONSTEXPR constexpr
#else
	#define MOVE(a) (a)
	#define CONSTEXPR
#endif

