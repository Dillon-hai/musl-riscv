static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
        void *old;
        int tmp;
        __asm__("li %1, 1\n"
                "1:\n\t"
                "lr.d %0, %2\n\t"
                "bne %0, %3, 1f\n\t"
                "sc.d %1, %4, %2\n\t"
                "bnez %1, 1b\n"
                "1:"
                : "=rJ"(old), "=rJ"(tmp), "+A"(*((long *)p))
                : "r"(t), "r"(s));
        return old;
}

static inline int a_cas(volatile int *p, int t, int s)
{
        int old, tmp;
        __asm__("li %1, 1\n"
                "1:\n\t"
                "lr.w %0, %2\n\t"
                "bne %0, %3, 1f\n\t"
                "sc.w %1, %4, %2\n\t"
                "bnez %1, 1b\n"
                "1:"
                : "=rJ"(old), "=rJ"(tmp), "+A"(*(p))
                : "r"(t), "r"(s));
        return old;
}

static inline int a_swap(volatile int *x, int v)
{
        int old;
        __asm__("amoswap.w.aq.rl %0, %2, %1"
                : "=rJ"(old), "+A"(*(x))
                : "r"(v));
        return old;
}

static inline int a_fetch_add(volatile int *x, int v)
{
        int tmp;
        __asm__("amoadd.w.aq.rl %0, %2, %1"
                :"=rJ"(tmp), "+A"(*(x))
                :"r"(v));
        return tmp;
}

static inline void a_inc(volatile int *x)
{
        a_fetch_add(x, 1);
}

static inline void a_dec(volatile int *x)
{
        a_fetch_add(x, -1);
}

static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
        int tmp;
        __asm__("amoand.d.aq.rl %0, %2, %1"
                :"=rJ"(tmp), "+A"(*(p))
                :"r"(v));
}

static inline void a_and(volatile int *p, int v)
{
        int tmp;
        __asm__("amoand.w.aq.rl %0, %2, %1"
                :"=rJ"(tmp), "+A"(*(p))
                :"r"(v));
}

static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
        int tmp;
        __asm__("amoor.d.aq.rl %0, %2, %1"
                :"=rJ"(tmp), "+A"(*(p))
                :"r"(v));
}

static inline void a_or_l(volatile void *p, long v)
{
        a_or_64(p, (uint64_t) v);
}

static inline void a_or(volatile int *p, int v)
{
        int tmp;
        __asm__("amoor.w.aq.rl %0, %2, %1"
                :"=rJ"(tmp), "+A"(*(p))
                :"r"(v));
}

static inline void a_store(volatile int *p, int x)
{
        __asm__("amoswap.w.aq.rl %zero, %1, %0"
                :"+A"(*(p))
                :"r"(x));
}
