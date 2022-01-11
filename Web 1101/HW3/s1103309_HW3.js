function progress()
{
	var txt = document.form.txt.value;

	var seq = txt.split("\n");
	var output="";
	for (var i = 0; i<20;i+=2)
	{
	    var result=calc(seq[i],seq[i+1]); //第i筆測資
		output=output+"<br>"+result; //串接上每一次的result
	}
    document.getElementById('out').innerHTML= output;
}

function calc(str1,str2)
{
    /* 
       str1 : first ogject
	   str2 : second object
    */
	var s1 = str1.split(","); //s1[0]:x1, s1[1]:y1 ...s1[7]
	var s2 = str2.split(","); 

	var answer = "";
    /*----------------- Your Code Start-------------*/
    var X1 = new Array ();
	var Y1 = new Array (); //X and Y for first object
	var X2 = new Array ();
	var Y2 = new Array (); //X and Y for second object

    for(var k=0;k<=6;k+=2)
    {
        X1.push(parseFloat(s1[k]));
		X2.push(parseFloat(s2[k]));
    }
    for(var k=1;k<=7;k+=2)
    {
		Y1.push(parseFloat(s1[k]));
		Y2.push(parseFloat(s2[k]));
	}
	X1.push(parseFloat(s1[0]));
	Y1.push(parseFloat(s1[1])); //go back to the first point to make a closed shape
	X2.push(parseFloat(s2[0]));
	Y2.push(parseFloat(s2[1])); //go back to the first point to make a closed shape

	var X3 = new Array ();
	var Y3 = new Array (); //new shape points

    for(var m=0;m<=3;m++)
    {
    	for(var n=0;n<=3;n++)
        {

            var b1 = X1[m+1]-X1[m];
    		var b2 = X2[n+1]-X2[n];
            var a1 = -1*(Y1[m+1]-Y1[m])
            var a2 = -1*(Y2[n+1]-Y2[n])
    		var c1 = a1*X1[m]+(b1*Y1[m]);
    		var c2 = a2*X2[n]+(b2*Y2[n]);

    		//now we have Line1 and Line2 equations "ax+by=c"

    		var delta = a1*b2 - a2*b1;
    		var deltaX = c1*b2 - c2*b1;
    		var deltaY = a1*c2 - a2*c1;

            if(delta!=0){
                var TempX = deltaX/delta;
                var TempY = deltaY/delta;
                //console.log('Range1',inRange(TempX,TempY,X1[m],Y1[m],X1[m+1],Y1[m+1]));
                //console.log('Range2',inRange(TempX,TempY,X2[n],Y2[n],X2[n+1],Y2[n+1]));

                if(inRange(TempX,TempY,X1[m],Y1[m],X1[m+1],Y1[m+1])&&inRange(TempX,TempY,X2[n],Y2[n],X2[n+1],Y2[n+1]))
                {
                    if(!exist(TempX,TempY,X3,Y3)){
                            X3.push(TempX);
                            Y3.push(TempY);
                    }
                }
            }
        }

     	if(inField(X1[m+1],Y1[m+1],X2[0],Y2[0],X2[1],Y2[1],X2[2],Y2[2],X2[3],Y2[3])){
                    X3.push(X1[m+1]);
                    Y3.push(Y1[m+1]);
        }
    }
    for(var m=0;m<=3;m++)
    {
        if(inField(X2[m],Y2[m],X1[0],Y1[0],X1[1],Y1[1],X1[2],Y1[2],X1[3],Y1[3])){
                //if in the first object
                X3.push(X2[m]);
                Y3.push(Y2[m]);
        }
    }
    console.log('X3',X3);
    console.log('Y3',Y3);

    answer = ArrangeAndArea(X3,Y3);
	return answer;
}

function inRange(Dx,Dy,x1,y1,x2,y2)
{
	var Xmin,Xmax,Ymin,Ymax;
	
	if(x1>x2){
		Xmax = x1;
		Xmin = x2;
	}else{
		Xmax = x2;
		Xmin = x1;
	}
	//console.log('Xmax',Xmax);
    //console.log('Xmin',Xmin);
	if(y1>y2){
		Ymax = y1;
		Ymin = y2;
	}else{
		Ymax = y2;
		Ymin = y1;
	}
	//console.log('Ymax',Ymax);
    //console.log('Ymin',Ymin);

	if(Dx>=Xmin&&Dx<=Xmax&&Dy>=Ymin&&Dy<=Ymax){
            return true;
	}
    return false;

}
function inField(Dx,Dy,x1,y1,x2,y2,x3,y3,x4,y4)
{
	/*-------------detemine if a point is in the other object-------------*/
    //外積will同號
    var a = (x2-x1)*(Dy-y1) - (y2-y1)*(Dx-x1);
    var b = (x3-x2)*(Dy-y2) - (y3-y2)*(Dx-x2);
    var c = (x3-x2)*(Dy-y2) - (y3-y2)*(Dx-x2);
    var d = (x4-x3)*(Dy-y3) - (y4-y3)*(Dx-x3);
    var e = (x1-x4)*(Dy-y4) - (y1-y4)*(Dx-x4);
    if(a>0&&b>0&&c>0&&d>0&&e>0){
        return true;
    }else if(a<0&&b<0&&c<0&&d<0&&e<0){
        return true;
    }else{
        return false;
    }

}
function exist(Dx,Dy,X,Y){
    for(var i=0;i<X.length;i++){
        if(Dx==X[i]&&Dy==Y[i]){
            return true;
        }
    }
    return false;
}

function ArrangeAndArea(X,Y){
    var Xmiddle=0,Ymiddle=0;
    var newX = new Array ();
    var newY = new Array ();
    for(var i = 0;i<X.length;i++){
        Xmiddle += X[i];
        Ymiddle += Y[i];
    }

    Xmiddle /= X.length;
    Ymiddle /= Y.length;


    for(var i = 0;i<X.length;i++){
        if(X[i]>=Xmiddle&&Y[i]>=Ymiddle){
            if(newY.length>0 && Y[i]>newY[newY.length-1]){
                var CacheX = newX[newX.length-1];
                var CacheY = newY[newY.length-1];
                newX[newX.length-1] = X[i];
                newY[newY.length-1] = Y[i];
                newX.push(CacheX);
                newY.push(CacheY);
            }else{
                newX.push(X[i]);
                newY.push(Y[i]);
            }
        }
    }
    var count = newY.length;
    for(var i = 0;i<X.length;i++){
        if(X[i]>Xmiddle&&Y[i]<Ymiddle){
            if(newY.length>count && Y[i]>newY[newY.length-1]){
                var CacheX = newX[newX.length-1];
                var CacheY = newY[newY.length-1];
                newX[newX.length-1] = X[i];
                newY[newY.length-1] = Y[i];
                newX.push(CacheX);
                newY.push(CacheY);
            }else{
                newX.push(X[i]);
                newY.push(Y[i]);
            }
        }
    }
    count = newX.length;
    for(var i = 0;i<X.length;i++){
        if(X[i]<=Xmiddle&&Y[i]<=Ymiddle){
            if(newX.length>count && X[i]>newX[newX.length-1]){
                var CacheX = newX[newX.length-1];
                var CacheY = newY[newY.length-1];
                newX[newX.length-1] = X[i];
                newY[newY.length-1] = Y[i];
                newX.push(CacheX);
                newY.push(CacheY);
            }else{
                newX.push(X[i]);
                newY.push(Y[i]);
            }
        }
    }
    count = newY.length;
    for(var i = 0;i<X.length;i++){
        if(X[i]<Xmiddle&&Y[i]>Ymiddle){
            if(newY.length>count && Y[i]<newY[newY.length-1]){
                var CacheX = newX[newX.length-1];
                var CacheY = newY[newY.length-1];
                newX[newX.length-1] = X[i];
                newY[newY.length-1] = Y[i];
                newX.push(CacheX);
                newY.push(CacheY);
            }else{
                newX.push(X[i]);
                newY.push(Y[i]);
            }
        }
    }
    newX.push(newX[0]);
	newY.push(newY[0]); //go back to the first point to make a closed shape
    console.log('newX',newX);
    console.log('newY',newY);
    //calculate area
    var area = 0;
    for(var m=0;m<=newX.length-2;m++){
        area += newX[m]*newY[m+1] - newX[m+1]*newY[m];
    }
    if(area<0){
        area*=-1;
    }
    area/=2;
    return area;
}
/*----------------- Your Code End --------------*/
