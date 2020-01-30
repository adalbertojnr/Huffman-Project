comp208 <- read.table("Comp_Data.txt", header = T, sep = "\t")

#Compute the largest y and x in the data
max_y <- max(comp208$Comparações_AVL, comp208$Comparações_ABB)
max_x <- max(comp208$Tamanho_AVL, comp208$Tamanho_ABB)

#Define colors to be used for AVL and BST
plot_colors <- c("black", 'red')

#Start PNG device to save output to Fig_Plot.png
png("Grafico_plotagem.png", height = 720, width = 1280, bg = "white")

#Plotting
plot(comp208$Tamanho_ABB, comp208$Comparações_ABB, type = "p", pch = 20, col = plot_colors[1],
     ylim = c(0, max_y), xlim = c(0, max_x), axes = FALSE, ann = FALSE)

#Change interval scale
axis(1, las = 1, at = ((max_x %% 100000)/10)*0:max_x)

axis(2, las = 1, at = ((max_y %% 100000)/10)*0:max_y)

box()

#Graph BST
lines(comp208$Tamanho_AVL, comp208$Comparações_AVL, type = "p", pch = 20, lty = 2, col = plot_colors[2])

#Create a title with red, bold/italic font
title(main = "Search Algorithm: AVL x BST", col.main = "black", font.main = 4)

#Label the x and y axes with dark green text
title(xlab = "Size", col.lab = rgb(0, 0, 0), cex.lab = 1.75, line = 2.5)
title(ylab = "Number of Comparisons", col.lab = rgb(0, 0, 0), cex.lab = 1.75, line = -2)

nameStruct <- c("ABB", "AVL")

legend(1, max_y, nameStruct, cex = 0.8, col = plot_colors, pch = 20:20, lty = 1:2);

#turn off device driver (to flush output to png)
dev.off()