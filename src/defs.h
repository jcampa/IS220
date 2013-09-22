#pragma once

#if __cplusplus > 199711L
	#define MOVE(a) std::move(a)
	#define CONSTEXPR constexpr
	#define NOEXCEPT noexcept
#else
	#define MOVE(a) (a)
	#define CONSTEXPR
	#define NOEXCEPT throw()
#endif

