#pragma once

#if __cplusplus > 199711L
	#define CXX11 1
	#define MOVE(a) std::move(a)
	#define CONSTEXPR constexpr
	#define NOEXCEPT noexcept
#else
	#define CXX11 0
	#define MOVE(a) (a)
	#define CONSTEXPR
	#define NOEXCEPT throw()
#endif

