if (arr1_i > arr2_i) {
      res_arr[res_arr_i] = arr1[res_arr_i];
      arr1_i--;
      printf("%d+_=%d\n", arr1[res_arr_i], res_arr[res_arr_i]);
    } else if (arr2_i > arr1_i) {
      res_arr[res_arr_i] = arr2[res_arr_i];
      arr2_i--;
      printf("_+%d=%d\n", arr2[res_arr_i], res_arr[res_arr_i]);
    } else {