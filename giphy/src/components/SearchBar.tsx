import * as React from 'react';
import TextField from '@material-ui/core/TextField';

class SearchBar extends React.Component<{onTermChange: any}> {
    constructor(props: any) {
        super(props);
        this.state = { term: '' }
    }

    onInputChange(term: any) {
        this.setState({term});
        this.props.onTermChange(term);
    }

    render() {
        return (
            <div className="search" id="test22">
                <TextField id="test2" label="Search..." variant="filled"  onChange={event => this.onInputChange(event.target.value)}/>
                {/* <input placeholder="Enter text to search for gifs!" onChange={event => this.onInputChange(event.target.value)} /> */}
            </div>
        );
    }
}

export default SearchBar;