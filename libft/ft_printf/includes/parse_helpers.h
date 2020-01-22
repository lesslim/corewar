/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:05:47 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:05:50 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HELPERS_H
# define PARSE_HELPERS_H

void	parse_flags(const char **s, t_param *param);
void	parse_width(const char **s, t_param *param, va_list args);
void	parse_precision(const char **s, t_param *param, va_list args);
void	parse_length(const char **s, t_param *param);
void	parse_type(const char **s, t_param *param);

#endif
