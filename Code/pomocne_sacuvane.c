int empty_place;
    i = (i+1)%7;
    empty_place = rand() % 3;
     if(i == 0){
       comet_array[6][0].z_pos = comet_array[6][0].z_pos + 0.5;
       comet_array[6][1].z_pos = comet_array[6][1].z_pos + 0.5; 
    }
    else{
        comet_array[i-1][0].z_pos = comet_array[i-1][0].z_pos + 0.5;
        comet_array[i-1][1].z_pos = comet_array[i-1][1].z_pos + 0.5;
    }

    comet_array[i][0].z_pos = -30;
    comet_array[i][1].z_pos = -30;
        
    switch(empty_place){
        case 0:
            comet_array[i][0].x_pos = 0;
            comet_array[i][1].x_pos = 6;
            break;
        case 1:
            comet_array[i][0].x_pos = -6;
            comet_array[i][1].x_pos = 6;
            break;
        case 2:
            comet_array[i][0].x_pos = -6;
            comet_array[i][1].x_pos = 0;
            break;
    }
  
    int j;
    for(j=0;j<7;j++){
        draw_comet(comet_array[j][0]);    
        draw_comet(comet_array[j][1]);
    }
    
    glutPostRedisplay();
   // glutTimerFunc(TIMER_INTERVAL1, comet_generate, TIMER_ID1);
