install.packages("ISLR")
library("ISLR")
install.packages("caTools")
library(caTools)
install.packages('neuralnet')
library(neuralnet)

datatmp = read.csv("C:\\Users\\Maxime\\Downloads\\CodeBlocks\\Indicators\\NN\\output.csv", header = TRUE)
prix = datatmp$close
perf=c()
for(i in seq(1:671)){
  x=(prix[i+1]/prix[i])-1
  x=x*1000
  if(x< -1){  perf=c(perf,0)}
  else{
    if(x>1){
      perf=c(perf,1)
    }
    else{
      perf=c(perf,(x+1)/2)
      
    }
  }
}
perf = c(perf,0)



maxs<-apply(datatmp[,2:12], 2, max)
mins<-apply(datatmp[,2:12], 2, min)

scaled.data <- as.data.frame(scale(datatmp[,2:12],center = mins, scale = maxs - mins))



data = cbind(perf,scaled.data)


set.seed(101)

split = sample.split(data$perf, SplitRatio = 0.7)
train = subset(data, split == TRUE)
test = subset(data, split == FALSE)

feats <- names(scaled.data)
f <- paste(feats,collapse=' + ')
f <- paste('perf ~',f)

f <- as.formula(f)


nn <- neuralnet(f,train,hidden=c(10),linear.output=FALSE)

predicted.nn.values <- compute(nn,test[2:12])

hhh<-function(x){
  if(x<0.35){return(0)}
  if(x>0.65){return(1)}
  return(0.5)
  }
predicted.nn.values$net.result <- sapply(predicted.nn.values$net.result,hhh)
predicted.nn.values$net.result
table(test$perf,predicted.nn.values$net.result)


