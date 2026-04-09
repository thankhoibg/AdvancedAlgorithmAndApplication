import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.FlowNetwork;
import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.FordFulkerson;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class BaseballElimination {

    private final int n;
    private final HashMap<String, Integer> teamIndices;
    private final String[] teamNames;
    private final int[] w, l, r;
    private final int[][] g;

    public BaseballElimination(String filename) {
        In in = new In(filename);
        this.n = in.readInt();
        this.teamIndices = new HashMap<>();
        this.teamNames = new String[n];
        this.w = new int[n];
        this.l = new int[n];
        this.r = new int[n];
        this.g = new int[n][n];

        for (int i = 0; i < n; i++) {
            String name = in.readString();
            teamIndices.put(name, i);
            teamNames[i] = name;
            w[i] = in.readInt();
            l[i] = in.readInt();
            r[i] = in.readInt();
            for (int j = 0; j < n; j++) {
                g[i][j] = in.readInt();
            }
        }
    }

    public int numberOfTeams() { return n; }
    public Iterable<String> teams() { return teamIndices.keySet(); }

    public int wins(String team) {
        validateTeam(team);
        return w[teamIndices.get(team)];
    }

    public int losses(String team) {
        validateTeam(team);
        return l[teamIndices.get(team)];
    }

    public int remaining(String team) {
        validateTeam(team);
        return r[teamIndices.get(team)];
    }

    public int against(String team1, String team2) {
        validateTeam(team1);
        validateTeam(team2);
        return g[teamIndices.get(team1)][teamIndices.get(team2)];
    }

    private void validateTeam(String team) {
        if (team == null || !teamIndices.containsKey(team)) {
            throw new IllegalArgumentException("Invalid team name");
        }
    }

    public boolean isEliminated(String team) {
        validateTeam(team);
        return getEliminationInfo(team) != null;
    }

    public Iterable<String> certificateOfElimination(String team) {
        validateTeam(team);
        return getEliminationInfo(team);
    }

    private List<String> getEliminationInfo(String team) {
        int x = teamIndices.get(team);
        int maxWinsX = w[x] + r[x];
        List<String> certificate = new ArrayList<>();

        // 1. Trivial Elimination
        for (int i = 0; i < n; i++) {
            if (w[i] > maxWinsX) {
                certificate.add(teamNames[i]);
                return certificate;
            }
        }

        // 2. Nontrivial Elimination (Maxflow)
        int numTeamsOther = n;
        int numGameNodes = (n * (n - 1)) / 2;
        int s = 0;
        int t = 1;
        int gameNodeStart = 2;
        int teamNodeStart = gameNodeStart + numGameNodes;

        FlowNetwork network = new FlowNetwork(2 + numGameNodes + numTeamsOther);
        double totalRemainingGames = 0;

        int gameNodeIdx = gameNodeStart;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Ignore games involving team x
                if (i == x || j == x) {
                    gameNodeIdx++;
                    continue;
                }

                if (g[i][j] > 0) {
                    // Source to Game node
                    network.addEdge(new FlowEdge(s, gameNodeIdx, g[i][j]));
                    // Game node to Team nodes
                    network.addEdge(new FlowEdge(gameNodeIdx, teamNodeStart + i, Double.POSITIVE_INFINITY));
                    network.addEdge(new FlowEdge(gameNodeIdx, teamNodeStart + j, Double.POSITIVE_INFINITY));
                    totalRemainingGames += g[i][j];
                }
                gameNodeIdx++;
            }
        }

        // Team nodes to Sink
        for (int i = 0; i < n; i++) {
            if (i == x) continue;
            int capacity = maxWinsX - w[i];
            // If capacity is negative, it should have been caught by trivial elimination
            network.addEdge(new FlowEdge(teamNodeStart + i, t, Math.max(0, capacity)));
        }

        FordFulkerson ff = new FordFulkerson(network, s, t);

        // If max flow is less than total games, team x is eliminated
        if (ff.value() < totalRemainingGames) {
            for (int i = 0; i < n; i++) {
                if (i == x) continue;
                // If the team vertex is on the source side of the min-cut
                if (ff.inCut(teamNodeStart + i)) {
                    certificate.add(teamNames[i]);
                }
            }
            return certificate;
        }

        return null;
    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
        for (String team : division.teams()) {
            if (division.isEliminated(team)) {
                StdOut.print(team + " is eliminated by the subset R = { ");
                for (String t : division.certificateOfElimination(team)) {
                    StdOut.print(t + " ");
                }
                StdOut.println("}");
            } else {
                StdOut.println(team + " is not eliminated");
            }
        }
    }
}