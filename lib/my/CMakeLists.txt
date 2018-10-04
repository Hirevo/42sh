
cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_STANDARD 11)

add_library(my STATIC
    src/my_fstrcat.c
    src/my_puterror.c
    src/my_memset.c
    src/my_putstr.c
    src/my_putchar.c
    src/my_put_nbr.c
    src/my_strcmp.c
    src/my_strstr.c
    src/my_strlen.c
    src/my_strcpy.c
    src/my_strcat.c
    src/my_strcatdup.c
    src/my_strncat.c
    src/my_strncpy.c
    src/my_strncmp.c
    src/my_revstr.c
    src/my_getnbr.c
    src/my_find_prime_sup.c
    src/my_is_prime.c
    src/my_isneg.c
    src/my_power_rec.c
    src/my_sort_int_table.c
    src/my_square_root.c
    src/my_str_isalpha.c
    src/my_showmem.c
    src/my_showstr.c
    src/my_str_islower.c
    src/my_str_isprintable.c
    src/my_str_isnum.c
    src/my_str_isupper.c
    src/my_strcapitalize.c
    src/my_strlowcase.c
    src/my_strupcase.c
    src/my_swap.c
    src/my_strdup.c
    src/my_strdup_until.c
    src/my_strndup.c
    src/my_printf.c
    src/parsing.c
    src/my_strdup.c
    src/nb_args.c
    src/convert_base.c
    src/size_nb.c
    src/my_int_to_char.c
)
target_include_directories(my PUBLIC src)
