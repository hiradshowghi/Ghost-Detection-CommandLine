#include <stdio.h>          // Including stdio gives us access to printf() and scanf()
#include <stdbool.h>

#define MAX_SIZE  16        // Maximum number of elements in any array

#define C_OK             0	// Success flag
#define C_ERR_ARR_FULL  -1	// Error code for array is full
#define C_ERR_BAD_EMF   -2	// Error code for an invalid emf_values value
#define C_ERR_BAD_RID   -3	// Error code for an invalid Room ID value

// Tip: You should likely include some more definitions to avoid "magic numbers"

// Note: These are "Forward Declarations". They tell the compiler that these functions exist, 
// but that they will be defined later. You can **not** change any of these lines, but you 
// may add additional "helper" functions if you wish and change the parameter names (not types).
// You MAY remove all of the comments you were provided with.
int get_data(int room_ids[], float emf_values[]);
int is_valid_room_id(int room_ids);
int is_valid_emf_values(float emf_values);
int print_data(int room_ids[], float emf_values[], int size);
int remove_values_under(float threshold, int room_ids[], float emf_values[], int size);

int remove_values_under(float threshold, int room_ids[], float emf_values[], int size){
  int new_size = 0;
  for (int i = 0; i < size; i++){
    if(emf_values[i] >= threshold){
      room_ids[new_size] = room_ids[i];
      emf_values[new_size]= emf_values[i];
      new_size++;
    }
  }

  return new_size;
}

int get_data(int room_ids[], float emf_values[]){
  int size = 0;
  int room_id;
  float emf_value;
  int errCode;

  while (size < MAX_SIZE) {
    printf("Enter a Room ID & EMF Value (-1 & -1 to stop)");
    scanf("%d %f", &room_id, &emf_value);

    if (room_id == -1 && emf_value == -1){
      return size;
    }

    errCode = is_valid_room_id(room_id);
    if(errCode != C_OK){
      printf("Invalid entry, enter a roomID between 350000 and 400000\n");
      continue;
    }

    errCode = is_valid_emf_values(emf_value);
    if(errCode != C_OK){
      printf("Invalid entry, enter a emf value between 0.00 and 5.00\n");
      continue;
    }

    room_ids[size] = room_id;
    emf_values[size] = emf_value;

    size++;
  }

  return C_ERR_ARR_FULL;
}

int print_data(int room_ids[], float emf_values[], int size){
  printf("%-10s %5s\n","Room ID","EMF");
  printf("================\n");
  for(int i = 0; i < size; i++){
    printf("%-11d %.2f\n",room_ids[i],emf_values[i]);
  }
  printf("----------------\n");
  printf("Total entries: %d\n",size);
}

int is_valid_room_id(int room_ids){
  if (350000 <= room_ids && room_ids <= 400000){
    return 0;
  }
  return -3;
}

int is_valid_emf_values(float emf_values){
  if (0.00 <= emf_values && emf_values <= 5.00){
    return 0;
  }
  return -2;
}

int main(){
  int room_ids[MAX_SIZE];
  float emf_values[MAX_SIZE];
  int size;

  size = get_data(room_ids, emf_values);
  print_data(room_ids, emf_values, size);

  size = remove_values_under(4.50,room_ids,emf_values,size);
  printf("Filtered Data:\n");
  print_data(room_ids, emf_values, size);

  return 0;
}

/*
  Function: example_function_documentation(int, int, float[])
  Purpose:  Displays example expected documentation for all functions except for main()
      in     var_name:    An in (or input) parameter is one that is read by the function but not modified
      out    var_name2:   An out (or output) parameter is one that is modified by the function but not read
      in/out var_name3:   An in/out parameter is one that is both read and modified by the function
       
  return:   the meaning of what's being returned, and any cases/conditions that would cause a different value to be returned
*/