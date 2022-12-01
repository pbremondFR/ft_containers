/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi_color_funcs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:21:48 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/22 21:12:03 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSI_COLOR_FUNCS_H
# define ANSI_COLOR_FUNCS_H

//Reset
# define RESET "\e[0m"

//Regular text
# define __BLK(x) ("\e[0;30m" x RESET)
# define __RED(x) ("\e[0;31m" x RESET)
# define __GRN(x) ("\e[0;32m" x RESET)
# define __YEL(x) ("\e[0;33m" x RESET)
# define __BLU(x) ("\e[0;34m" x RESET)
# define __MAG(x) ("\e[0;35m" x RESET)
# define __CYN(x) ("\e[0;36m" x RESET)
# define __WHT(x) ("\e[0;37m" x RESET)

//Regular bold text
# define __BBLK(x) ("\e[1;30m" x RESET)
# define __BRED(x) ("\e[1;31m" x RESET)
# define __BGRN(x) ("\e[1;32m" x RESET)
# define __BYEL(x) ("\e[1;33m" x RESET)
# define __BBLU(x) ("\e[1;34m" x RESET)
# define __BMAG(x) ("\e[1;35m" x RESET)
# define __BCYN(x) ("\e[1;36m" x RESET)
# define __BWHT(x) ("\e[1;37m" x RESET)

//Regular underline text
# define __UBLK(x) ("\e[4;30m" x RESET)
# define __URED(x) ("\e[4;31m" x RESET)
# define __UGRN(x) ("\e[4;32m" x RESET)
# define __UYEL(x) ("\e[4;33m" x RESET)
# define __UBLU(x) ("\e[4;34m" x RESET)
# define __UMAG(x) ("\e[4;35m" x RESET)
# define __UCYN(x) ("\e[4;36m" x RESET)
# define __UWHT(x) ("\e[4;37m" x RESET)

//Regular background
# define __BLKB(x) ("\e[40m" x RESET)
# define __REDB(x) ("\e[41m" x RESET)
# define __GRNB(x) ("\e[42m" x RESET)
# define __YELB(x) ("\e[43m" x RESET)
# define __BLUB(x) ("\e[44m" x RESET)
# define __MAGB(x) ("\e[45m" x RESET)
# define __CYNB(x) ("\e[46m" x RESET)
# define __WHTB(x) ("\e[47m" x RESET)

//High intensty background 
# define __BLKHB(x) ("\e[0;100m" x RESET)
# define __REDHB(x) ("\e[0;101m" x RESET)
# define __GRNHB(x) ("\e[0;102m" x RESET)
# define __YELHB(x) ("\e[0;103m" x RESET)
# define __BLUHB(x) ("\e[0;104m" x RESET)
# define __MAGHB(x) ("\e[0;105m" x RESET)
# define __CYNHB(x) ("\e[0;106m" x RESET)
# define __WHTHB(x) ("\e[0;107m" x RESET)

//High intensty text
# define __HBLK(x) ("\e[0;90m" x RESET)
# define __HRED(x) ("\e[0;91m" x RESET)
# define __HGRN(x) ("\e[0;92m" x RESET)
# define __HYEL(x) ("\e[0;93m" x RESET)
# define __HBLU(x) ("\e[0;94m" x RESET)
# define __HMAG(x) ("\e[0;95m" x RESET)
# define __HCYN(x) ("\e[0;96m" x RESET)
# define __HWHT(x) ("\e[0;97m" x RESET)

//Bold high intensity text
# define __BHBLK(x) ("\e[1;90m" x RESET)
# define __BHRED(x) ("\e[1;91m" x RESET)
# define __BHGRN(x) ("\e[1;92m" x RESET)
# define __BHYEL(x) ("\e[1;93m" x RESET)
# define __BHBLU(x) ("\e[1;94m" x RESET)
# define __BHMAG(x) ("\e[1;95m" x RESET)
# define __BHCYN(x) ("\e[1;96m" x RESET)
# define __BHWHT(x) ("\e[1;97m" x RESET)

#endif
