import * as React from 'react';
import Axios, * as axi from 'axios';

import SearchBar from './components/SearchBar';


const placeHolderArray = [
  "https://media1.giphy.com/media/1qfb3aFqldWklPQwS3/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
  "https://media2.giphy.com/media/10l8fc00NMNJNm/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
  "https://media1.giphy.com/media/1qfb3aFqldWklPQwS3/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
  "https://media2.giphy.com/media/10l8fc00NMNJNm/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
  "https://media1.giphy.com/media/1qfb3aFqldWklPQwS3/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
  "https://media2.giphy.com/media/10l8fc00NMNJNm/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
  "https://media1.giphy.com/media/1qfb3aFqldWklPQwS3/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
  "https://media2.giphy.com/media/10l8fc00NMNJNm/giphy.gif?cid=dad748735f5cd59cfa8aaafc9e608c29253e7c8f1e19a506&rid=giphy.gif",
]

const GifTEST = (image: any) => {
  return (
  <div>
      <iframe src="https://giphy.com/embed/10l8fc00NMNJNm" ></iframe>
      {/* <img src={image} /> */}
  </div>
)
};


const MapArray = () =>{

  const demoState = placeHolderArray.map((imageURL: string)=>{
    return <GifTEST gifUrl={imageURL} />
  })
  return(
    <div>
      {demoState}
    </div>
  )
}


const Gif = (image: any) => {
  return (
  <div className="gif-item">
      <img src={image.gif.images.original.url} />
  </div>
)
};

const GifArray = (props: any) => {
  if(props.gifs.length === 0 && props.text !== ""){
      return (<div style={{textAlign:"center", fontSize:"200%", color:"#EBEFC9", top:"-50px"}}> No Gif's were found under this keyword</div>) //backgroundColor:"#E8CAAF"
  }
  const Gifs = props.gifs.map((image: any) => {
      // console.log(image);
      return <Gif key={image.id} gif={image} />
  });

  return (
      <div className="gif-list">{Gifs}</div>
  );
};



interface Props {
  name: string;
}

interface GIFS {
  gifs: any[],
  text: string
}

class App extends React.Component<Props, GIFS> {
  
  constructor(props: any) {
    super(props);
    
    this.state = {
      gifs: [],
      text: ""
    }
    this.handleTermChange = this.handleTermChange.bind(this);
  }

  handleTermChange(term: any) {
    const url = `http://api.giphy.com/v1/gifs/search?q=${term}&api_key=Yg1Lsn4WSF63Pz5bpMVraA3NIqQm1NUj`;
    Axios.get(url).then((response) => {
      // console.log(response.data.data)
      this.setState({gifs: response.data.data})
      this.setState({text: term})
    });
  }

  render() {
    const { name } = this.props;
    return (
      <div style={{display:"flex"}}>
        <div style={{width:"69%"}}>
          <div id="test">{name} by Nik</div>
          <div>
            <SearchBar onTermChange={this.handleTermChange} />
            <GifArray gifs={this.state.gifs} text={this.state.text} />
          </div>
        </div>
        <div style={{width:"29%", textAlign:"center", fontSize:"200%", color:"#EBEFC9"}}>
          Favourites!!!
          <MapArray/>
        </div>
      </div>
    );
  }
}

export default App;
