# $NetBSD: cond-func-defined.mk,v 1.15 2025/06/28 22:39:28 rillig Exp $
#
# Tests for the defined() function in .if conditions.

DEF=		defined
${:UA B}=	variable name with spaces

.if !defined(DEF)
.  error
.endif

# Horizontal whitespace (space tab) after the opening parenthesis is ignored.
.if !defined( 	DEF)
.  error
.endif

# Horizontal whitespace (space tab) before the closing parenthesis is ignored.
.if !defined(DEF 	)
.  error
.endif

# The argument of a function must not directly contain whitespace.
# expect+1: Missing ")" after argument "A" for "defined"
.if !defined(A B)
.  error
.endif

# If necessary, the whitespace can be generated by an expression.
.if !defined(${:UA B})
.  error
.endif

# expect+1: Missing ")" after argument "DEF" for "defined"
.if defined(DEF
.  error
.else
.  error
.endif

# Variables from .for loops are not defined.
# See directive-for.mk for more details.
.for var in value
.  if defined(var)
.    error
.  else
# In .for loops, expressions based on the loop variables are substituted at
# evaluation time.  There is no actual variable involved, even if the code in
# the makefiles looks like it.
.  endif
.endfor

# Expressions in the argument of a function call don't have to be defined.
.if defined(${UNDEF})
.  error
.endif

# Neither of the conditions is true.  Before July 2020, the right-hand
# condition was evaluated even though it was irrelevant.
.if defined(UNDEF) && ${UNDEF:Mx} != ""
.  error
.endif

all: .PHONY
