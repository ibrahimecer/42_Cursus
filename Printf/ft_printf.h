/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecer <iecer@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:34:05 by iecer             #+#    #+#             */
/*   Updated: 2024/01/17 14:11:52 by iecer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_putstr(char *str);
int	ft_putchar(char c);
int	ft_putint(int number);
int	ft_putunsigned(unsigned int number);
int	ft_putuphex(unsigned int number);
int	ft_putdownhex(unsigned int number);
int	ft_putptr(unsigned long number, int i);
int	ft_printf(const char *format, ...);

#endif