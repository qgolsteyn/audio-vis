#ifndef	OBJECT_H
#define	OBJECT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

extern const void * Object;		/* new(Object); */

struct Object {
	const struct Class * class;	/* object's description */
};

void * new (const void * class, ...);
void delete (void * self);

const void * classOf (const void * self);
size_t sizeOf (const void * self);

void * ctor (void * self, va_list * app);
void * dtor (void * self);
int differ (const void * self, const void * b);

extern const void * Class;	/* new(Class, "name", super, size
										sel, meth, ... 0); */

struct Class {
	const struct Object _;			/* class' description */
	const char * name;				/* class' name */
	const struct Class * super;		/* class' super class */
	size_t size;					/* class' object's size */
	void * (* ctor) (void * self, va_list * app);
	void * (* dtor) (void * self);
	int (* differ) (const void * self, const void * b);
};

#define	name(p)	(((const struct Class *)(p)) -> name)

const void * super (const void * self);	/* class' superclass */

void * super_ctor (const void * class, void * self, va_list * app);
void * super_dtor (const void * class, void * self);
int super_differ (const void * class, const void * self, const void * b);

#endif
