import matplotlib.pyplot as plt
  

with open("./results/test4.txt", "r") as file:
    points_x=[]
    points_y=[]
    points=[]
    for str in file:

            if str[0]=="A":
                break
            
            list=str.split(" ")
                        
            if(len(list) == 2):      
                pointx=float(list[0])
                pointy=float(list[1][:-1])
                points.append([pointx,pointy])
            elif(len(list) == 4):
                point1x=list[0]
                point1y=list[1]
                point2x=list[2]
                point2y=list[3][:-1]

                point1=[point1x,point1y]
                point2=[point2x,point2y]
                points_x.append(float(point1[0]))
                points_y.append(float(point1[1]))
                
                points_x.append(float(point2[0]))
                points_y.append(float(point2[1]))

    plt.plot(points_x,points_y)
    plt.show()
    print(points_x)