import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objects as go
import scpalgo  # Import the updated C++ module

# Generate algorithm states using Ford-Fulkerson
capacities = [
    [0, 10, 10, 0, 0, 0],
    [0, 0, 0, 4, 8, 0],
    [0, 0, 0, 0, 9, 10],
    [0, 0, 0, 0, 0, 10],
    [0, 0, 0, 6, 0, 10],
    [0, 0, 0, 0, 0, 0],
]
source, sink = 0, 5
states = scpalgo.ford_fulkerson(capacities, source, sink)

# Fixed node positions for visualization
pos = {
    0: (0, 1),
    1: (1, 2),
    2: (1, 0),
    3: (2, 2),
    4: (2, 0),
    5: (3, 1),
}

def build_graph(state):
    nodes = list(range(len(state.residualGraph)))
    edges = [
        (u, v, state.residualGraph[u][v])
        for u in range(len(state.residualGraph))
        for v in range(len(state.residualGraph[u]))
        if state.residualGraph[u][v] > 0
    ]

    node_x = [pos[node][0] for node in nodes]
    node_y = [pos[node][1] for node in nodes]
    node_colors = ["green" if state.visited[node] else "blue" for node in nodes]

    edge_x, edge_y = [], []
    edge_colors = []
    for u, v, _ in edges:
        edge_x.extend([pos[u][0], pos[v][0], None])
        edge_y.extend([pos[u][1], pos[v][1], None])
        edge_colors.append("red" if (u, v) in state.exploredEdges else "gray")

    return node_x, node_y, edge_x, edge_y, node_colors, edge_colors

# Dash App
app = dash.Dash(__name__)
app.layout = html.Div([
    dcc.Graph(id="graph"),
    dcc.Slider(
        id="slider",
        min=0,
        max=len(states) - 1,
        step=1,
        value=0,
        marks={i: f"Step {i}" for i in range(len(states))}
    ),
])

@app.callback(
    Output("graph", "figure"),
    [Input("slider", "value")]
)
def update_graph(step):
    state = states[step]
    node_x, node_y, edge_x, edge_y, node_colors, edge_colors = build_graph(state)

    fig = go.Figure()

    for i in range(len(edge_x) // 3):
        fig.add_trace(go.Scatter(
            x=edge_x[i * 3:(i + 1) * 3],
            y=edge_y[i * 3:(i + 1) * 3],
            line=dict(width=2, color=edge_colors[i]),
            mode="lines"
        ))

    fig.add_trace(go.Scatter(
        x=node_x,
        y=node_y,
        mode="markers+text",
        marker=dict(size=20, color=node_colors),
        text=[str(node) for node in pos.keys()],
        textposition="top center"
    ))

    fig.update_layout(
        title=f"Ford-Fulkerson Algorithm - Step {step + 1}",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False),
        yaxis=dict(showgrid=False, zeroline=False),
    )

    return fig

if __name__ == "__main__":
    app.run_server(debug=True)
