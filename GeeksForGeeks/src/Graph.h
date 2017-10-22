/*
 * Graph.h
 *
 *  Created on: Oct 16, 2017
 *      Author: srikanth
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#define DIRECTIONAL 1
#define NON_DIRECTIONAL 2

typedef struct adj_node_s {
	int dest;
	int weight;
	struct adj_node_s *next;
}adj_node_t;

/*Per vertex data and adj list.*/
typedef struct adj_list_s {
	void *data;
	int visited;
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
int add_edge(graph_t *graph, int v, int u, int bidirectional);
void print_graph(graph_t *graph);
void bfs_traversal_graph(graph_t* graph, int v);
void dfs_traversal_graph(graph_t *graph, int v);




#endif /* GRAPH_H_ */
