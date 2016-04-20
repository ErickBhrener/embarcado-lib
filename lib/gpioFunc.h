/**	@file gpioFunc.h

  @attention Copyright:Fundacao CPqD
  @attention Centro de Pesquisa e Desenvolvimento em Telecomunicacoes
  @attention Classification: Restrita
  @attention Division: DRC - Diretoria de Redes Convergentes

  @version v1
  @author Francisco Helder C. dos Santos
  @date 05/17/2013
  @brief This file describes the Test 'class'. 



  @since VER	| DATE      | COMMENTS
  @since v0   - 05/17/2013 	- File creation
  @since v1   - 05/17/2013 	- Changes
  */

#ifndef GPIOFUNC_H_
#define GPIOFUNC_H_

/*
 * =====================================================================================
 *
 *       Filename:  gpioFunc.h
 *
 *    Description:  gpio function
 *
 *        Version:  1.0
 *        Created:  30/10/2014 08:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Benoit François-Marie Christian Roulle
 *        Company:  Fundacao CPqD
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

 /****************************************************************
 *  * Constants
 *   ****************************************************************/
 
#define OUT 0
#define IN 1


int initGpio(unsigned int gpio);
int releaseGpio(unsigned int gpio);
int gpio_set_dir(unsigned int gpio, unsigned int out_flag);
int gpio_set_value(unsigned int gpio, unsigned int value);
int gpio_get_value(unsigned int gpio, unsigned int *value);
int gpio_set_edge(unsigned int gpio, char *edge);
int gpio_fd_open(unsigned int gpio);
int gpio_fd_close(int fd);

#endif /* GPIOFUNC_H_ */
