#include "utils/logger.h"
#include "libft/ft_printf_fd.h"
#include <stdarg.h>

const char *convert_log_level_to_string(t_log_level level)
{
	switch (level)
	{
	case LOG_DEBUG:
		return COLOR_DEBUG "[DEBUG]" RESET;
	case LOG_INFO:
		return COLOR_INFO "[INFO]" RESET;
	case LOG_WARNING:
		return COLOR_WARNING "[WARNING]" RESET;
	case LOG_ERROR:
		return COLOR_ERROR "[ERROR]" RESET;
	case LOG_CRITICAL:
		return COLOR_CRITICAL "[CRITICAL]" RESET;
	default:
		return "[UNKNOWN]";
	}
}

void log_message(t_log_level log_level, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	if (VERBOSE)
	{
		ft_printf_fd(2, "%s ", convert_log_level_to_string(log_level));
		ft_vprintf_fd(2, format, args);
	}
	else if (log_level > LOG_WARNING)
	{
		ft_printf_fd(2, "shell: ");
		ft_vprintf_fd(2, format, args);
	}
	va_end(args);
}
