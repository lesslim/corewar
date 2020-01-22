.name "cork"
.comment "screw this"

l2:		
	sti r1, %:live0, %1
	sti r1, %:live1, %1
	and r1, %0, r1

live0:
	live %1
	
live1:
	live %1
	zjmp %:live0
