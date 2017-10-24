/*
 * Graph.h
 *
 *  Created on: Oct 16, 2017
 *      Author: srikanth
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <limits.h>

#define DIRECTIONAL 1
#define NON_DIRECTIONAL 2

#define NEG_INFINITY INT_MIN


typedef struct adj_node_s {
	int dest;
	int weight;
	struct adj_node_s *next;
}adj_node_t;

/*Per vertex data and adj list.*/
typedef struct adj_list_s {
	void *data;
	int visited;
	int dist;
	int cnt;
	adj_node_t *head;
}adj_list_t;


typedef struct graph_s {
	int vertices; /*Num of vertices in the graph*/
	adj_list_t *adj_arr; /*Array of pointers (size vertices)
	                       which gives the adjaceny of each
	                       vertex.*/
} graph_t;


graph_t *create_graph(int vertices);
void destroy_graph(graph_t *graph);
int add_vertex(graph_t* graph, int v);
int add_edge(graph_t *graph, int v, int u, int bidirectional, int weight);
void print_graph(graph_t *graph);
void bfs_traversal_graph(graph_t* graph, int v);
void dfs_traversal_graph(graph_t *graph, int v);
void topological_sort_graph(graph_t* graph);
void lonest_path_directed_acyclic_graph(graph_t *graph, int src);
int find_mother_vertex_in_graph(graph_t* graph, int* mother_vertex);
void printKcoresOfGraph(graph_t *graph, int k);



#endif /* GRAPH_H_ */
