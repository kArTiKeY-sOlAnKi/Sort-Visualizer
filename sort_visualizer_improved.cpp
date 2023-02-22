#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>
#include <vector>
using namespace std ;

void draw_state(vector<int> &v, SDL_Renderer *renderer, int red, int blue)
{
	int index = 0 ;
	for (int i : v)
	{
		if (index == red)
		{
			SDL_SetRenderDrawColor(renderer,255,0,0,255) ;
		}

		else if (index == blue)
		{
			SDL_SetRenderDrawColor(renderer,0,0,153,255) ;
		}

		else
		{
			SDL_SetRenderDrawColor(renderer,255,255,255,255) ; // white
		}

		SDL_RenderDrawLine(renderer,index,99,index,i) ;

		index++ ;
	}
}

void draw(int *arr, SDL_Renderer *renderer, int red, int blue, int n)
{
	int index = 0 ;
	for (int i = 0; i < n; i++)
	{
		if (index == red)
		{
			SDL_SetRenderDrawColor(renderer,255,0,0,255) ;
		}

		else if (index == blue)
		{
			SDL_SetRenderDrawColor(renderer,0,0,153,255) ;
		}

		else
		{
			SDL_SetRenderDrawColor(renderer,255,255,255,255) ; // white
		}

		SDL_RenderDrawLine(renderer,index,99,index,i) ;

		index++ ;
	}
}

int partition(int *arr, int start, int end, SDL_Renderer *renderer)
{
	// creating pointing variables
	int i = start - 1 ;
	int j = start ;
	int pivot = arr[end] ;

	for ( ; j <= end - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i = i + 1 ;
			swap(arr[i],arr[j]) ;
			/*draw(arr, renderer, i, j, end) ;
	    	SDL_RenderPresent(renderer) ;
	    	SDL_Delay(10) ;*/ // broken working part
		}
	}

	swap(arr[i+1],arr[end]) ;

	SDL_SetRenderDrawColor(renderer,0,0,0,255) ;
	SDL_RenderClear(renderer) ;
	draw(arr,renderer,i,j,end) ;
	SDL_RenderPresent(renderer) ;
	SDL_Delay(100) ;

	return i + 1 ;
}

void merge (int *v, int start, int end, SDL_Renderer *renderer) 
{
    int i = start ;
    int mid = (start + end) / 2 ;
    int j = mid + 1 ;
    int k = 0 ;
    int temp[end - start + 1] ;

    while (i <= mid && j <= end) 
    {
        if (v[i] <= v[j]) 
        {
            temp[k++] = v[i++] ;
        } 
        else 
        {
            temp[k++] = v[j++] ;
        }
    }

    while (i <= mid) 
    {
        temp[k++] = v[i++] ;
    }

    while (j <= end) 
    {
        temp[k++] = v[j++] ;
    }

    for (k = 0; k < end-start+1 ; k++) 
    {
        v[start+k] = temp[k] ;
    }

    // SDL_SetRenderDrawColor(renderer,0,0,0,255) ;
	// SDL_RenderClear(renderer) ;
    draw(v, renderer, start, end, (end-start+1)) ;
    SDL_RenderPresent(renderer) ;
    SDL_Delay(15) ;
}

void mergeSort (int *arr, int start, int end, int n, SDL_Renderer *renderer) 
{
    if (start >= end) 
    {
        return ;
    }

    int mid = (start + end) / 2 ;
    mergeSort(arr, start, mid, n, renderer) ;
    mergeSort(arr, mid + 1, end, n, renderer) ;
    merge(arr, start, end, renderer) ;
    // draw(arr, renderer, start, end, n) ;
    // SDL_RenderPresent(renderer) ;
    // SDL_Delay(50) ;
}

void quickSort (int *arr, int start, int end, SDL_Renderer *renderer)
{
	// base case
	if (start > end)
	{
		return ;
	}

	int p = partition(arr,start,end,renderer) ;
	// left part
	quickSort(arr,start,p-1,renderer) ;
	// right part
	quickSort(arr,p+1,end,renderer) ;
}

int main (int argv, char** args)
{
	random_device rd ;
	uniform_int_distribution<> d(1,99) ;

	vector<int> v ;
	int ch ;

	for (int i = 0; i < 100; i++)
	{
		v.push_back(d(rd)) ;
	}

	int n = v.size() ;
	int arr[n] ;

	// for (int i = 100; i >=0 ; i--)
	// {
	// 	v.push_back(i) ;
	// }

	cout<<"*****SORT VISUALIZER*****"<<endl ;
	cout<<endl ;
	cout<<"The Unsorted Array is : "<<endl ;
	for (int i = 0; i < v.size(); i++)
	{
		cout<<v[i]<<" " ; 
	}

	cout<<endl ;
	cout<<endl ;
	cout<<"*****SORT VISUALIZER MENU*****"<<endl ;
	cout<<"Enter the Sorting Technique"<<endl ;
	cout<<"1. Brute Force"<<endl ;
	cout<<"2. Selection Sort"<<endl ;
	cout<<"3. Bubble Sort"<<endl ;
	cout<<"4. Insertion Sort"<<endl ;
	cout<<"5. Merge Sort"<<endl ;
	cout<<"6. Quick Sort"<<endl ;

	cout<<"Enter your response : " ;
	cin>>ch ;

	if (ch == 1)
	{
		// Brute Technique to sort vector
		cout<<endl<<"You have selected Brute Force Technique"<<endl ;

		SDL_Window *window = NULL ;
		SDL_Renderer *renderer = NULL ;
		SDL_CreateWindowAndRenderer(100*10,100*10,0,&window,&renderer) ;
		SDL_RenderSetScale(renderer,10,10) ;

		for (int i = 0; i < v.size(); i++)
		{
			for (int j = i; j < v.size(); j++)
			{
				if (v[j] < v[i])
				{
					swap(v[j],v[i]) ;
				}
				SDL_SetRenderDrawColor(renderer,0,0,0,255) ;
				SDL_RenderClear(renderer) ;

				draw_state(v,renderer,i,j) ;

				SDL_RenderPresent(renderer) ;
				SDL_Delay(1) ;
			}
		}
	}

	else if (ch == 2)
	{
		cout<<endl<<"You have selected Selection Sort Technique"<<endl ;

		SDL_Window *window = NULL ;
		SDL_Renderer *renderer = NULL ;
		SDL_CreateWindowAndRenderer(100*10,100*10,0,&window,&renderer) ;
		SDL_RenderSetScale(renderer,10,10) ;

		for (int i = 0; i < v.size() - 1; i++)
		{
			int min_index = i ;
			for (int j = i+1; j < v.size();j++)
			{
				if (v[j] < v[min_index])
				{
					min_index = j ;
				}
			}

			swap(v[i],v[min_index]) ;
				
			SDL_SetRenderDrawColor(renderer,0,0,0,255) ;
			SDL_RenderClear(renderer) ;

			draw_state(v,renderer,i,min_index) ;

			SDL_RenderPresent(renderer) ;
			SDL_Delay(100) ;
		}
	}

	else if (ch == 3)
	{
		cout<<endl<<"You have selected Bubble Sort Technique"<<endl ;

		SDL_Window *window = NULL ;
		SDL_Renderer *renderer = NULL ;
		SDL_CreateWindowAndRenderer(100*10,100*10,0,&window,&renderer) ;
		SDL_RenderSetScale(renderer,10,10) ;

		int n = v.size() ;

		for (int i = 1; i <= n-1; i++)
		{
			for (int j = 0; j <= (n-1-i); j++)
			{
				if (v[j] > v[j+1])
				{
					swap(v[j],v[j+1]) ;
				}

				SDL_SetRenderDrawColor(renderer,0,0,0,255) ;
				SDL_RenderClear(renderer) ;

				draw_state(v,renderer,i,j) ;

				SDL_RenderPresent(renderer) ;
				SDL_Delay(1) ;
			}
		}
	}

	else if (ch == 4)
	{
		cout<<endl<<"You have selected Insertion Sort Technique"<<endl ;

		SDL_Window *window = NULL ;
		SDL_Renderer *renderer = NULL ;
		SDL_CreateWindowAndRenderer(100*10,100*10,0,&window,&renderer) ;
		SDL_RenderSetScale(renderer,10,10) ;

		int n = v.size() ;

		for (int i = 1; i <= n-1; i++)
		{
			int ele = v[i] ;
			int j = i - 1 ;
			
			while (j >= 0 and v[j] > ele)
			{
				v[j+1] = v[j] ;
				j-- ;
			}
			v[j+1] = ele ;

			SDL_SetRenderDrawColor(renderer,0,0,0,255) ;
			SDL_RenderClear(renderer) ;

			draw_state(v,renderer,i,j) ;

			SDL_RenderPresent(renderer) ;
			SDL_Delay(100) ;
		}
	}

	else if (ch == 5)
	{
		cout<<endl<<"You have selected Merge Sort Technique"<<endl ;

		SDL_Window *window = NULL ;
		SDL_Renderer *renderer = NULL ;
		SDL_CreateWindowAndRenderer(100*10,100*10,0,&window,&renderer) ;
		SDL_RenderSetScale(renderer,10,10) ;

		int n = v.size() ;

		for (int i = 0; i < n; i++)
		{
			arr[i] = v[i] ;
		}

		mergeSort(arr, 0, n - 1, n, renderer) ;
	}

	else if (ch == 6)
	{
		cout<<endl<<"You have selected Quick Sort Technique"<<endl ;

		SDL_Window *window = NULL ;
		SDL_Renderer *renderer = NULL ;
		SDL_CreateWindowAndRenderer(100*10,100*10,0,&window,&renderer) ;
		SDL_RenderSetScale(renderer,10,10) ;

		int n = v.size() ;

		for (int i = 0; i < n; i++)
		{
			arr[i] = v[i] ;
		}

		quickSort(arr,0,n-1,renderer) ;
	}


	if (ch < 5)
	{
	 	cout<<"Sorted Array is : "<<endl ;
		for (int i = 0; i < v.size(); i++)
		{
			cout<<v[i]<<" " ;
		}
	}

	else
		+
SDL_SetRenderDrawColor(renderer,0,0,0,255) ;
	SDL_RenderClear(renderer) ;	{
		cout<<"Sorted Array is : "<<endl ;
		for (int i = 0; i < v.size(); i++)
		{
			cout<<arr[i]<<" " ;
		}
	}

	return 0 ;
}