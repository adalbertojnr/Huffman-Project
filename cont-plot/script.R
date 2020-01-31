graf<-read.table("Comp_Data.txt", header = TRUE, sep = " ")
plot(graf$ABB~graf$Valor, main="Árvore de Busca Binaria X Árvore Binaria de Busca Balanceada", xlab="Valores", ylab="Comparações", col="blue")
points(graf$AVL~graf$Valor, col="red")