
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define  MAPING( X1 ,  X2 ,  Y1 ,  Y2 ,  ADC)\
((((s64)ADC-X1)*((s64)Y2 - Y1))/((s64)X2 - X1 ))+(s64)Y1


#define  TRUE    1
#define  FALSE   0

#define  READ_BIT(reg,bit)    ((reg>>bit)&1)
#define  SET_BIT(reg,bit)     (reg=reg|(1<<bit))
#define  CLR_BIT(reg,bit)     (reg=reg&~(1<<bit))
#define  TOG_BIT(reg,bit)     (reg=reg^(1<<bit))
#define  Write_PORT(reg,data) (reg = data)
#define  WRITE_BIT(reg,bit,val)    (reg=(((reg)&~(1<<bit))|(val<<bit)))




#endif /* BIT_MATH_H_ */
