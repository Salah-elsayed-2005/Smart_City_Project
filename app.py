import dash
import dash_bootstrap_components as dbc
from dash import dcc, html
from dash.dependencies import Input, Output, State
import plotly.graph_objects as go
import smart_city  # Import compiled C++ module via pybind11

# Fetch node coordinates and graph data
city_coordinates = smart_city.get_city_coordinates()

road_network = smart_city.get_road_network()

# Prepare node and edge data for visualization
nodes = [
    {
        "id": i,
        "x": coord[0],
        "y": coord[1],
        "label": f"Node {i}"
    }
    for i, coord in enumerate(city_coordinates)
]

def get_edges():
    edges = []
    for i, row in enumerate(road_network):
        for j, weight in enumerate(row):
            if weight > 0:
                edges.append({"source": i, "target": j, "weight": weight})
    return edges

edges = get_edges()

def plot_graph():
    fig = go.Figure()

    # Add edges to the plot with capacities
    for edge in edges:
        x0, y0 = city_coordinates[edge["source"]]
        x1, y1 = city_coordinates[edge["target"]]
        fig.add_trace(go.Scatter(
            x=[x0, x1], y=[y0, y1],
            mode="lines+text",
            line=dict(color="black", width=2),
            text=["", f"{edge['weight']}", ""],
            textposition="middle center",
            hoverinfo="none"
        ))

    # Add nodes to the plot
    for node in nodes:
        fig.add_trace(go.Scatter(
            x=[node["x"]], y=[node["y"]],
            mode="markers+text",
            marker=dict(size=15, color="skyblue", line=dict(color="black", width=2)),
            text=node["label"],
            textposition="top center",
            hoverinfo="text"
        ))

    # Update layout for better visualization
    fig.update_layout(
        title="City Map Visualization",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        margin=dict(l=10, r=10, t=50, b=10),
        plot_bgcolor="white"
    )
    return fig

app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])
app.title = "Smart City Visualization"

app.layout = dbc.Container(
    [
        dbc.Row(
            dbc.Col(
                html.H1("Smart City Algorithm Visualization", className="text-center text-primary my-4"),
                width=12
            )
        ),
        dbc.Row(
            [
                dbc.Col(
                    [
                        html.H5("Algorithm Parameters", className="text-secondary mb-3"),
                        html.Label("Select Source Node:"),
                        dcc.Input(id="source-input", type="number", min=0, max=len(road_network)-1, step=1, value=0,
                                  className="form-control mb-2"),
                        html.Label("Select Sink Node:"),
                        dcc.Input(id="sink-input", type="number", min=0, max=len(road_network)-1, step=1, value=5,
                                  className="form-control mb-3"),
                        dbc.Button("Run Algorithm", id="run-button", color="primary", className="mt-3 w-100"),
                        html.Hr(),
                        html.H5("Events", className="text-secondary mb-3"),
                        dbc.Button("Trigger Earthquake", id="earthquake-button", color="danger", className="mb-2 w-100"),
                        dcc.Input(id="earthquake-node", type="number", placeholder="Damaged Node", className="form-control mb-2",min=0, max=len(road_network)-1,step=1),
                        dbc.Button("Trigger Maintenance", id="maintenance-button", color="warning", className="mb-2 w-100"),
                        dcc.Input(id="maintenance-node", type="number", placeholder="Damaged Node", className="form-control mb-2",min=0, max=len(road_network)-1,step=1),
                        dbc.Button("Trigger Traffic Congestion", id="traffic-button", color="info", className="mb-2 w-100"),
                        dcc.Input(id="traffic-node", type="number", placeholder="Congested Node", className="form-control mb-2",min=0, max=len(road_network)-1,step=1),
                    ],
                    width=3,
                    className="bg-light p-4 rounded shadow-sm"
                ),
                dbc.Col(
                    dcc.Graph(
                        id="city-map",
                        figure=plot_graph(),
                        style={"height": "80vh"}
                    ),
                    width=9
                )
            ]
        ),
        dbc.Row(
            [
                dbc.Col(
                    dcc.Slider(
                        id="slider",
                        min=0,
                        max=0,
                        step=1,
                        value=0,
                        marks={},
                        tooltip={"placement": "bottom", "always_visible": True},
                    ),
                    width=12
                )
            ],
            className="mt-4"
        ),
        dbc.Row(
            dbc.Col(
                html.Div(id="metrics", className="text-center mt-3 text-info", style={"fontSize": "18px"}),
                width=12
            ),
            className="mt-3"
        )
    ],
    fluid=True
)

@app.callback(
    [Output("city-map", "figure"), Output("metrics", "children")],
    [Input("run-button", "n_clicks")],
    [State("source-input", "value"), State("sink-input", "value")]
)
def run_shortest_path(n_clicks, source, sink):
    if n_clicks is None or source is None or sink is None or source == sink:
        return plot_graph(), "Invalid source/sink selection."

    # Call the start_shortest_path function from the C++ module
    route = smart_city.start_shortest_path(source, sink)

    # Prepare the updated graph with the shortest path
    fig = plot_graph()

    # Highlight the shortest path on the graph
    for i in range(len(route) - 1):
        x0, y0 = city_coordinates[route[i]]
        x1, y1 = city_coordinates[route[i + 1]]
        fig.add_trace(go.Scatter(
            x=[x0, x1], y=[y0, y1],
            mode="lines",
            line=dict(color="red", width=4),
            hoverinfo="none"
        ))

    return fig, f"Shortest path from {source} to {sink}: {route}"


@app.callback(
    Output("metrics", "children"),
    [Input("earthquake-button", "n_clicks"), Input("earthquake-node", "value")]
)
def trigger_earthquake(n_clicks, node):
    if n_clicks:
        if node is not None:
            earthquake = smart_city.Earthquake(node)
            earthquake.trigger()
            return f"Earthquake triggered at node {node}."
        else:
            return "Please specify a damaged node for the earthquake."

@app.callback(
    Output("metrics", "children"),
    [Input("maintenance-button", "n_clicks"), Input("maintenance-node", "value")]
)
def trigger_maintenance(n_clicks, node):
    if n_clicks:
        if node is not None:
            maintenance = smart_city.Maintenance(node)
            maintenance.trigger()
            return f"Maintenance triggered at node {node}."
        else:
            return "Please specify a damaged node for the maintenance."

@app.callback(
    Output("metrics", "children"),
    [Input("traffic-button", "n_clicks"), Input("traffic-node", "value")]
)
def trigger_traffic_congestion(n_clicks, node):
    if n_clicks:
        if node is not None:
            traffic = smart_city.TrafficCongestion(node)
            traffic.trigger()
            return f"Traffic congestion triggered at node {node}."
        else:
            return "Please specify a congested node for the traffic event."

if __name__ == "__main__":
    app.run_server(debug=True)
