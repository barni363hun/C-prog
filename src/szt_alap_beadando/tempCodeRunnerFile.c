
  do {
    res.res_arr[i] = (ans - (10 * (ans / 10)));
    ans /= 10;
    i++;
  } while (ans != 0);