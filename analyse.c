
int analyse1(int pox)
{
    int fs= 100;
//    int pox[] = {}
    int lengte = sizeof(pox)/sizeof(int);

    /* Afgeleide */
    int l=0;
	for (l;l<lengte-1;l++){
        pox[l]=pox[l+1]-pox[l];
    }
    lengte = sizeof(pox)/sizeof(int)-1;
    /* Window moving integrator */
	int r=0;
	int pox2[1000] = {0};
	for (r; r<lengte; r++ ) {
        double som = 0;
		if (r < 20){
            int q = 0;
            for (q;q<r;q++){
				som=som+pox[q];
            }
            if (r>1){
            pox2[r] = som/(r-1);
            }
            if (r<2){
            pox2[r] = som;
            }
		}
		if (r>=20) {
            int q = r-20;
            for(q;q<r;q++){
                som=pox[q]+som;
            }
            pox2[r] = som/20;
		}
        som = 0;
    }
    lengte = sizeof(pox)/sizeof(int);

    /* Instellen van de variabelen */
    int t=0,u=0,x[6]={0};
	double y[6]={0};
	float max = 0;
    int index = 1,toestand = 0, z = 0, size = 0;
	float maximum1 =0, maximum2 = 0;
	float ggetal = 0;
	int getal = 0;

	/* Opstellen van de drempelwaarde = threshold */
	for (u;u<2*fs;u++){
		if (pox2[u]>=max){
			max=pox2[u];
        }
	}
	double threshold = 0.7*max;
    /* De uiteindelijke lus voor het vinden van de pieken */
	for (t;t<lengte;t++){

	    for (z;z<4;z++){
	        if (x[z] != 0 && x[z+1]==0) {
                size = z;
	        }
	    }

		if (toestand == 0 && pox[t] <= threshold){
			toestand = 0;


            if (pox2[t] > maximum1){
				maximum1 = pox2[t];

				if (size > 1){
					ggetal = ((x[size] - x[size-1]) + (x[size-1] - x[size-2]))/2;
					}
				if (size > 1 && (t - x[size]) > (ggetal + ggetal/2)){
					x[size+1]=t;
					y[size+1]=maximum1;
					maximum1 = 0;
					threshold = 0.6*y[size+1];
					size = size+1;
				}
			}
		}


		if (pox2[t]>= threshold){
			toestand = 1;
			if (pox2[t] > maximum2){
				maximum2 = pox2[t];
				index = t;
			}
        }

		if (toestand==1 && pox2[t] < threshold){
			x[size+1] = index;
			y[size+1] = maximum2;
			index = 0;
			maximum2 = 0;
			toestand = 0;
			size = size+1;

			if (size > 1){
				if (x[size]-x[size-1] < 0.2*fs){
					if (y[size] > y[size-1]){
						x[size-1]=x[size];
						y[size-1]=y[size];
						x[size]=0;
						y[size]=0;
						size = size-1;
					}
					else {
                        x[size] =0;
						y[size]=0;
						size = size-1;
					}
				}
			}
		}
        if (size > 0){
            double b = x[size];
            double a = x[size-1];
            getal = 1/(b-a)*fs*60;
            if (size > 1){
                double c = x[size-2];
                int vorig_getal = 1/(a-c)*fs*60;
            if (getal > 1.5*vorig_getal){
                getal = 1.2*vorig_getal;
                }
            }
        threshold=y[size-1]/2+y[size]/10;
        }

    }
	return getal;
}
