/*
 * gpio.h
 *
 *  Created on: 18.07.2019
 *      Author: Besitzer
 */

#ifndef GPIO_H_
#define GPIO_H_


#define GPIO_read(_name_)           ((_name_##_GPIO_Port->IDR) & (_name_##_Pin))
#define GPIO_write(_name_,_value_)  \
  if (_value_) {GPIO_set(_name_);} \
  else {GPIO_clr(_name_);}
#define GPIO_toggle(_name_) GPIO_write(_name_,!GPIO_read(_name_))

#define GPIO_output(_port_, _bit_)          (PORT##_port_.PDR.BIT.B##_bit_ = 1)
#define GPIO_set(_port_, _bit_)            (PORT##_port_.PODR.BIT.B##_bit_ = 1)
#define GPIO_clr(_port_, _bit_)            (PORT##_port_.PODR.BIT.B##_bit_ = 0)



#endif /* GPIO_H_ */
