-- Table: Run
CREATE TABLE AnalysisRunInfo (
    id INTEGER PRIMARY KEY,            -- Unique ID
    timestamp DATETIME NOT NULL,       -- Timestamp when analysis was performed
    descriptiomn TEXT,                 -- A description of the purpose of the analysis run
    author TEXT                        -- Optionally the name of the person who ran the analysis 
);

-- Table: Node
CREATE TABLE Node (
    id INTEGER PRIMARY KEY,                                    -- Unique ID
    parent_id INTEGER,                                         -- The optional id of the parent node
    name TEXT NOT NULL,                                        -- The namme of the node
    node_type_id INTEGER NOT NULL,                             -- The node type
    source_file_id INTEGER NOT NULL,                           -- The source file where the node was found
    begin_line_no INTEGER NOT NULL,                            -- The line number where the node source code begins
    end_line_no INTEGER NOT NULL,                              -- The line number where the node source code ends
    lines_of_code_metric INTEGER,                              -- The optional lines of code metric
    complexity INTEGER,                                        -- The optional cylomatic complexity metric for functions 
    documentation TEXT,                                        -- The optional documentation as found in the source code
    annotation TEXT,                                           -- An optional annotation based on human or ai evaluation

    FOREIGN KEY(parent_id) REFERENCES Node(id),
    FOREIGN KEY(node_type_id) REFERENCES NodeType(id),
    FOREIGN KEY(source_file_id) REFERENCES SourceFile(id)
);

-- Table: Edge
CREATE TABLE Edge (
    id INTEGER PRIMARY KEY,                                    -- Unique ID
    source_id INTEGER NOT NULL,                                -- The source node of the edge
    target_id INTEGER NOT NULL,                                -- The target node of the edge
    edge_type_id INTEGER NOT NULL,                             -- The edge type
    strength INTEGER NOT NULL,                                 -- The edge strength
    source_file_id INTEGER NOT NULL,                           -- The source file where the edge was found
    line_no INTEGER NOT NULL,                                  -- The line number where the edge was found
    annotation TEXT,                                           -- An optional annotation based on human or ai evaluation
    
    FOREIGN KEY(source_id) REFERENCES Node(id),
    FOREIGN KEY(target_id) REFERENCES Node(id),
    FOREIGN KEY(edge_type_id) REFERENCES EdgeType(id),
    FOREIGN KEY(source_file_id) REFERENCES SourceFile(id)
);

-- Table: NodeType
CREATE TABLE NodeType (
    id INTEGER PRIMARY KEY,                                    -- Unique ID
    text TEXT NOT NULL UNIQUE                                  -- Name of tye node type
);

-- Table: EdgeType
CREATE TABLE EdgeType (
    id INTEGER PRIMARY KEY,                                    -- Unique ID
    text TEXT NOT NULL UNIQUE                                  -- Name of the edge type
);

-- Table: SourceFile
CREATE TABLE SourceFile (
    id INTEGER PRIMARY KEY,                                    -- Unique ID
    filename TEXT NOT NULL UNIQUE                              -- The full path of the source file
);
