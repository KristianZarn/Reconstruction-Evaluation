function intervals = missing_intervals(x)
    
    intervals = [];
    for i = 1:length(x)-1
        step_diff = x(i+1) - x(i);
        
        if (step_diff > 1) 
            intervals = [intervals; i, i+1];
        end
    end
end