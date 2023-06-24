#include <stdarg.h>
#include <stdlib.h>

/**
 * _printf - prints formatted output
 * @format: format string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
 va_list args;
 int printed_chars;

 printed_chars = 0;
 va_start(args, format);
 if (format)
  printed_chars = parse_and_print(format, args);
 va_end(args);

 return (printed_chars);
}

/**
 * parse_and_print - parses and prints the format string
 * @format: format string
 * @args: variable argument list
 *
 * Return: number of characters printed
 */
int parse_and_print(const char *format, va_list args)
{
 int i, j, printed_chars;
 char *str;
 print_func_t print_func;
 specifier_t specifiers[] = {
  {"c", print_char},
  {"s", print_string},
  {"%", print_percent},
  {NULL, NULL}
 };

 i = 0;
 printed_chars = 0;
 while (format && format[i])
 {
  if (format[i] == '%')
  {
   i++;
   print_func = get_print_func(format[i], specifiers);
   if (print_func)
   {
    j = i + 1;
    while (format[j] && !is_specifier(format[j]))
     j++;
    str = get_arg_str(format + i, j - i, args);
    if (str)
    {
     printed_chars += print_func(str);
     free(str);
    }
    i = j;
   }
   else if (format[i])
   {
    _putchar(format[i]);
    printed_chars++;
   }
  }
  else
  {
   _putchar(format[i]);
   printed_chars++;
  }
  i++;
 }

 return (printed_chars);
}

/**
 * get_print_func - gets the appropriate print function for a specifier
 * @specifier: specifier character
 * @specifiers: array of specifier_t structs
 *
 * Return: pointer to print function, or NULL if specifier not found
 */
print_func_t get_print_func(char specifier, specifier_t *specifiers)
{
 int i;

 for (i = 0; specifiers[i].specifier; i++)
 {
  if (specifiers[i].specifier[0] == specifier)
   return (specifiers[i].print_func);
 }

 return (NULL);
}

/**
 * get_arg_str - gets the string argument for a specifier
 * @format: format string
 * @length: length of specifier
 * @args: variable argument list
 *
 * Return: pointer to string argument, or NULL if specifier not found
 */
char *get_arg_str(const char *format, int length, va_list args)
{
 if (length == 1)
  return (get_char_arg(args));
 else if (length == 2)
  return (get_str_arg(args));
 else if (length == 0)
  return (strdup(""));
 else
  return (NULL);
}

/**
 * is_specifier - checks if a character is a valid specifier
 * @c: character to check
 *
 * Return: 1 if specifier, 0 otherwise
 */
int is_specifier(char c)
{
 return (c == 'c' || c == 's' || c == '%');
}

