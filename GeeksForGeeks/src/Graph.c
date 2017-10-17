/*
 * Graph.c
 *
 *  Created on: Oct 16, 2017
 *      Author: srikanth
 */

#include "Graph.h"



graph_t *create_graph(int vertices)
{
	graph_t *newG;

	if (vertices <= 0) {
		return NULL;
	}

	newG = (graph_t*)malloc(sizeof(graph_t));
	if (!newG) {
		return NULL;
	}
	memset(newG, 0, sizeof(graph_t));

	newG->vertices = vertices;

	newG->adj_arr = (adj_list_t*)malloc(sizeof(adj_list_t) * vertices);
	if (!newG->adj_arr) {
		free(newG);
		return NULL;
	}

	memset(newG->adj_arr, 0, sizeof(adj_list_t) * vertices);

	return newG;
}


int add_vertex(graph_t* graph, int v)
{
	return 0;
}

int add_edge(graph_t *graph, int v, int u)
{
	if (!graph || (v < 0) || (u < 0) ||
		(v >= graph->vertices) || (u >= graph->vertices)) {
		return -1;
	}
}
