#if __cplusplus > 199711L
	#define MOVE(a) std::move(a)
#else
	#define MOVE(a) (a)
#endif
