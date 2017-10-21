/*
 * Graph.c
 *
 *  Created on: Oct 16, 2017
 *      Author: srikanth
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
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

void destroy_graph(graph_t *graph)
{

}

int add_vertex(graph_t* graph, int v)
{
	return 0;
}

int add_edge(graph_t *graph, int v, int u)
{
	adj_node_t* new_edge[2];

	if (!graph || (v < 0) || (u < 0) ||
		(v >= graph->vertices) || (u >= graph->vertices)) {
		return -1;
	}

	new_edge[0] = (adj_node_t*)malloc(sizeof(adj_node_t));
	new_edge[1] = (adj_node_t*)malloc(sizeof(adj_node_t));

	if (!new_edge[0] || !new_edge[1]) {
		if (new_edge[0]) {
			free(new_edge[0]);
		}

		if (new_edge[1]) {
			free(new_edge[1]);
		}
		return -1;
	}

	new_edge[0]->dest = u;
	new_edge[0]->next = graph->adj_arr[v].head;
	graph->adj_arr[v].head = new_edge[0];

	new_edge[1]->dest = u;
	new_edge[1]->next = graph->adj_arr[v].head;
	graph->adj_arr[v].head = new_edge[1];

	return 1;

}
