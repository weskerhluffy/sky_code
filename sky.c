/*
 * sky.c
 *
 *  Created on: 24/12/2018
 *      Author: ernestoalvarado
 */

// XXX: http://poj.org/problem?id=3904
// XXX: https://blog.csdn.net/Danliwoo/article/details/48933157
// XXX: https://github.com/tainzhi/acm/blob/master/poj/3904.c

#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#include <sys/time.h>
#endif
#include <math.h>
#include <stdint.h>
#include <ctype.h>

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX ULONG_MAX
#endif

#define CACA_COMUN_TAM_MAX_LINEA (16*200000)
#define CACA_LOG_MAX_TAM_CADENA 2000

#define CACA_COMUN_BUF_STATICO_TAM 1000
#define CACA_COMUN_BUF_STATICO (char[CACA_COMUN_BUF_STATICO_TAM] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2

#define CACA_COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define CACA_COMUN_IDX_INVALIDO ((natural)CACA_COMUN_VALOR_INVALIDO)
#define CACA_COMUN_FUNC_STATICA static

typedef char byteme;
typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_NIMADRES
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){while(1){printf("");};abort();}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug(formato, args...) 0;
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

#define caca_comun_calloc_local(tipo) (&(tipo){0})

void caca_log_debug_func(const char *format, ...);

#ifndef ONLINE_JUDGE
CACA_COMUN_FUNC_STATICA void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CACA_COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

CACA_COMUN_FUNC_STATICA void caca_comun_timestamp(char *stime) {
	time_t ltime;
	long ms;
#ifndef ONLINE_JUDGE
	struct tm result;
	struct timespec spec;
#endif
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

#ifndef ONLINE_JUDGE
	caca_comun_current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}

#endif
#ifdef CACA_COMUN_LOG
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
	"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
	+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
	char cadena_timestamp[100] = {'\0'};

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
	setbuf(stdout, NULL);
}
#endif

#ifdef CACA_COMUN_LOG
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, natural tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%1d", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	int i, j;
	natural inicio_buffer_act = 0;
	for (i = 0; i < filas_tam; i++) {
		caca_comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
				buffer + inicio_buffer_act);
		inicio_buffer_act += strlen(buffer + inicio_buffer_act);
		buffer[inicio_buffer_act++] = '\n';
		/*		caca_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
	}
	return buffer;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%llu", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
#else
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_natural(
		natural *arreglo, natural tam_arreglo, char *buffer) {
	return NULL;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	return NULL;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	return NULL;
}
#endif

#define caca_comun_arreglo_a_cadena_entero_largo_sin_signo_buf_local(a,a_tam) caca_comun_arreglo_a_cadena_entero_largo_sin_signo(a,a_tam,CACA_COMUN_BUF_STATICO)
#define caca_comun_arreglo_a_cadena_buf_local(a,a_tam) caca_comun_arreglo_a_cadena(a,a_tam,CACA_COMUN_BUF_STATICO)
#define caca_comun_arreglo_a_cadena_natural_buf_local(a,a_tam) caca_comun_arreglo_a_cadena_natural(a,a_tam,CACA_COMUN_BUF_STATICO)

CACA_COMUN_FUNC_STATICA void caca_comun_strreplace(char s[], char chr,
		char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

CACA_COMUN_FUNC_STATICA int caca_comun_lee_matrix_long_stdin(tipo_dato *matrix,
		int *num_filas, int *num_columnas, int num_max_filas,
		int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(CACA_COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, CACA_COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		caca_comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			caca_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

CACA_COMUN_FUNC_STATICA natural caca_comun_cuenta_bitchs(tipo_dato num) {
	natural bitch_cnt = 0;
	tipo_dato num_mod = 0;
	num_mod = num;
	while (num_mod) {
		num_mod &= ~(num_mod & (-num_mod));
		bitch_cnt++;
	}
	return bitch_cnt;
}

CACA_COMUN_FUNC_STATICA char caca_comun_letra_a_valor_minuscula(char letra) {
	return letra - 'a';
}

CACA_COMUN_FUNC_STATICA natural caca_comun_max_natural(natural *nums,
		natural nums_tam) {
	natural max = 0;
	int i = 0;

	for (i = 0; i < nums_tam; i++) {
		natural num_act = nums[i];
		if (num_act > max) {
			max = num_act;
		}
	}

	return max;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_trimea(char *cad, natural cad_tam) {
	char c = cad[0];
	char tmp = '\0';
	natural i = 0;
	natural j = 0;

	caca_log_debug("entrada %s cad_tam %u", cad, cad_tam);
	while (j < cad_tam && cad[j] != '\0') {
		caca_log_debug("en j %u car %c", j, cad[j]);
		while (j < cad_tam && !isalpha(cad[j])) {
			caca_log_debug("brincando j %u car %c", j, cad[j]);
			j++;
		}
		caca_log_debug("aora j %u car %c", j, cad[j]);
		if (j == cad_tam) {
			caca_log_debug("q ped");
			break;
		}
		tmp = cad[i];
		cad[i] = cad[j];
		cad[j] = tmp;
		i++;
		j++;
	}
	caca_log_debug("mierda '%c'", cad[j]);

	i = 0;
	while (isalpha(cad[i++]))
		;
	caca_log_debug("salida %s", cad);
	cad[i - 1] = '\0';

	return cad;
}

#endif

#define CACA_COMUN_LIMPIA_MEM(m,s) (memset(m,0,s))
#define CACA_COMUN_LIMPIA_MEM_STATICA(m) (memset(m,0,sizeof(*(m))))

CACA_COMUN_FUNC_STATICA bool caca_comun_es_digito(char c) {
	return c >= '0' && c <= '9';
}

CACA_COMUN_FUNC_STATICA byteme caca_comun_caracter_a_num(char c) {
	return c - '0';
}

CACA_COMUN_FUNC_STATICA void caca_comun_invierte_arreglo_byteme(byteme *a,
		natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		byteme t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

CACA_COMUN_FUNC_STATICA void caca_comun_invierte_arreglo_natural(natural *a,
		natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		natural t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

CACA_COMUN_FUNC_STATICA natural caca_comun_encuentra_minimo_natural(natural *a,
		natural a_tam) {
	natural min = CACA_COMUN_VALOR_INVALIDO;
	natural i;
	for (i = 0; i < a_tam; i++) {
		if (min > a[i]) {
			min = a[i];
		}
	}
	return min;
}

CACA_COMUN_FUNC_STATICA natural caca_comun_mcd(natural a, natural b) {
	natural r = CACA_COMUN_VALOR_INVALIDO;
	while (a && b) {
		natural tmp = b;
		b = a % b;
		a = tmp;
	}

	if (!a) {
		r = b;
	}
	if (!b) {
		r = a;
	}
	return r;
}

#endif

#if 1

#define PRIMOS_CACA_MAX ((int)1E4)

natural primos_caca[PRIMOS_CACA_MAX + 1] = { 0 };
natural primos_caca_tam = 0;
bool primos_caca_es_primo[PRIMOS_CACA_MAX + 1] = { 0 };
typedef void (*primos_caca_primo_encontrado_cb)(natural primo,
		natural idx_primo, void *cb_ctx);
typedef void (*primos_caca_compuesto_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto_origen, void *cb_ctx);

typedef void (*primos_caca_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

typedef void (*primos_caca_no_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

CACA_COMUN_FUNC_STATICA natural primos_caca_criba(natural limite,
		primos_caca_primo_encontrado_cb primo_cb,
		primos_caca_compuesto_encontrado_cb compuesto_cb,
		primos_caca_divisible_encontrado_cb divisible_encontrado_cb,
		primos_caca_no_divisible_encontrado_cb no_divisible_encontrado_cb,
		void *cb_ctx) {
	caca_log_debug("primos asta %u", limite);
	assert_timeout(limite<=PRIMOS_CACA_MAX);
	natural i, j;
	for (i = 2; i <= limite; i++) {
		primos_caca_es_primo[i] = verdadero;
	}
	for (i = 2; i <= limite; i++) {
		if (primos_caca_es_primo[i]) {
			primos_caca[primos_caca_tam++] = i;
			if (primo_cb) {
				primo_cb(i, primos_caca_tam - 1, cb_ctx);
			}
		}
		for (j = 0; j < primos_caca_tam && primos_caca[j] * i <= limite; j++) {
			primos_caca_es_primo[primos_caca[j] * i] = falso;
			if (compuesto_cb) {
				compuesto_cb(primos_caca[j], j, i, cb_ctx);
			}
			if (!(i % primos_caca[j])) {
				if (divisible_encontrado_cb) {
					divisible_encontrado_cb(primos_caca[j], j, i, cb_ctx);
				}
				break;
			} else {
				if (no_divisible_encontrado_cb) {
					no_divisible_encontrado_cb(primos_caca[j], j, i, cb_ctx);
				}
			}
		}
	}
	caca_log_debug("generados %u primos", primos_caca_tam);
	return primos_caca_tam;
}

#endif

#if 1
#define MORBIUS_MAX_MIERDA PRIMOS_CACA_MAX

int morbius[MORBIUS_MAX_MIERDA + 1] = { [1]=1 };

typedef struct morbius_datos {
	int *morbius;
} morbius_datos;

void morbius_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	morbius_datos *g = cb_ctx;

	g->morbius[compuesto * primo] = 0;
	caca_log_debug("divisible %u %d", compuesto*primo,
			g->morbius[compuesto*primo]);
}
void morbius_no_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	morbius_datos *g = cb_ctx;

	g->morbius[compuesto * primo] = g->morbius[compuesto] * -1;
	caca_log_debug("indivisible %u de %u %d", compuesto*primo, compuesto,
			g->morbius[compuesto*primo]);
}

void morbius_primo_encontrado_cb(natural primo, natural idx_primo, void *cb_ctx) {
	morbius_datos *g = cb_ctx;
	g->morbius[primo] = -1;
	caca_log_debug("primo enc %u %d", primo, g->morbius[primo]);
}
#endif

#define SKY_MAX_NUM MORBIUS_MAX_MIERDA

CACA_COMUN_FUNC_STATICA entero_largo sky_combinaciones(entero_largo n) {
	return n * (n - 1) * (n - 2) * (n - 3) / 24;
}

CACA_COMUN_FUNC_STATICA void sky_cuenta_multiplos(natural n, natural *multiplos,
		natural multiplos_tam) {
	natural n_sqrt = floor(sqrt(n));
	assert_timeout(n_sqrt < multiplos_tam);
	for (int i = 1; i <= n_sqrt; i++) {
		if (!(n % i)) {
			natural ci = n / i;
			multiplos[i]++;
			multiplos[ci]++;
		}
	}
	if (n_sqrt * n_sqrt == n) {
		multiplos[n_sqrt]--;
	}
}

CACA_COMUN_FUNC_STATICA entero_largo sky_core(natural *nums, natural nums_tam,
		morbius_datos *m) {
	natural *multiplos = calloc(SKY_MAX_NUM + 1, sizeof(natural));
	assert_timeout(multiplos);
	entero_largo no_primos_relativos = 0;

	for (natural i = 0; i < nums_tam; i++) {
		natural n = nums[i];
		sky_cuenta_multiplos(n, multiplos, SKY_MAX_NUM + 1);
	}

	for (natural i = 2; i <= SKY_MAX_NUM; i++) {
		entero_largo multiplos_i = multiplos[i];
		caca_log_debug("i %u multiplos %llu", i, multiplos_i);
		if (multiplos_i > 3) {
			caca_log_debug("comb %llu morbius %d",
					sky_combinaciones(multiplos_i), m->morbius[i]);
			no_primos_relativos += sky_combinaciones(multiplos_i)
					* m->morbius[i];
		}
	}

	entero_largo combinaciones_totales = sky_combinaciones(nums_tam);
	caca_log_debug("comb total %llu", combinaciones_totales);

	entero_largo r = combinaciones_totales + no_primos_relativos;

	free(multiplos);

	return r;
}

CACA_COMUN_FUNC_STATICA void sky_main() {
	morbius_datos *m = caca_comun_calloc_local(morbius_datos);
	natural *nums = calloc(SKY_MAX_NUM, sizeof(natural));
	assert_timeout(nums);
	m->morbius = morbius;
	primos_caca_criba(MORBIUS_MAX_MIERDA, morbius_primo_encontrado_cb, NULL,
			morbius_divisible_encontrado_cb, morbius_no_divisible_encontrado_cb,
			m);

	natural n = 0;
	while (scanf("%u\n", &n) > 0) {
		for (natural i = 0; i < n; i++) {
			scanf("%u", nums + i);
		}
		entero_largo r = sky_core(nums, n, m);
		printf("%llu\n", r);
	}
}

int main(void) {
	sky_main();
	return EXIT_SUCCESS;
}

