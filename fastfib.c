#include <stdio.h>
#include <gmp.h>
#include <sys/time.h>

/* O(n) */
void fib(mpz_t in, mpz_t out) {
	register int i, j, k, tmp;
	mpz_t f[3];
	mpz_t n;

	if(!mpz_cmp_ui(in, 0) || !mpz_cmp_ui(in, 1)) {
		mpz_set(out, in);
		return;
	}

	i = 0, j = 1, k = 2;
	mpz_inits(n, f[0], f[1], f[2], 0);
	mpz_set(n, in);
	mpz_set_ui(f[0], 1);
	mpz_set_ui(f[1], 1);

	while(mpz_cmp_ui(n, 2) > 0) {
		mpz_add(f[j], f[j], f[i]);
		mpz_set(f[k], f[i]);

		tmp = i;
		i = j;
		j = k;
		k = tmp;

		mpz_sub_ui(n, n, 1);
	}

	mpz_set(out, f[i]);

	mpz_clear(n);
	mpz_clear(f[i]);
	mpz_clear(f[j]);
	mpz_clear(f[k]);
}

/* TODO O(log n) */

int main(void) {
	struct timeval start, stop;
	double t;
	mpz_t n, m;

	mpz_inits(n, m, 0);
	mpz_set_ui(n, 0xffff);

	gettimeofday(&start, 0);
	fib(n, m);
	gettimeofday(&stop, 0);

	t = (double)(stop.tv_sec - start.tv_sec) * 1000.0f + (double)(stop.tv_usec - start.tv_usec);

	gmp_printf("fib(%Zd) = %Zd\ntime: %.2fms\n", n, m, t);

	mpz_clear(n);
	mpz_clear(m);
	return 0;
}
