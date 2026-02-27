# GitHub Pages Deployment

This repository uses GitHub Pages to host the WebAssembly version of Nanosaur, making it playable directly in web browsers.

## Live Site

**Play Nanosaur in your browser:** https://lachanbwwright.github.io/Nanosaur-android/

## How It Works

The deployment is fully automated via GitHub Actions:

1. **Build Trigger**: The workflow runs automatically on every push to the `master` branch, or can be triggered manually via workflow dispatch.

2. **Build Process** (`.github/workflows/BuildWasm.yml`):
   - Sets up Emscripten SDK
   - Builds SDL3 for WebAssembly (with caching for speed)
   - Compiles Nanosaur to WebAssembly
   - Packages the game files along with the landing page
   - Adds `.nojekyll` file to prevent Jekyll processing

3. **Deployment**:
   - Uses `peaceiris/actions-gh-pages@v4` action
   - Deploys to the `gh-pages` branch
   - GitHub Pages serves the content from this branch

## Site Structure

```
/ (root)
├── index.html          # Landing page with game info and controls
├── .nojekyll          # Prevents Jekyll from processing files
└── game/
    ├── index.html     # The actual game (Emscripten shell)
    ├── Nanosaur.js    # Emscripten JavaScript glue code
    ├── Nanosaur.wasm  # Compiled WebAssembly binary
    └── Nanosaur.data  # Embedded game data files
```

## GitHub Pages Settings

To enable GitHub Pages on your fork:

1. Go to repository Settings → Pages
2. Set **Source** to "Deploy from a branch"
3. Select the `gh-pages` branch
4. Set folder to `/ (root)`
5. Save

The workflow will automatically create and update the `gh-pages` branch.

## Local Development

To test the WebAssembly build locally before deploying:

```bash
# Build the WebAssembly version
python3 build.py --wasm

# Serve locally
cd build-wasm
python3 -m http.server 8080

# Open http://localhost:8080/Nanosaur.html in your browser
```

## Features

The GitHub Pages deployment includes:
- **Instant play**: No installation or downloads required
- **Cross-platform**: Works on any device with a modern web browser
- **Level editor integration**: Custom terrain file loading via JavaScript
- **Cheat menu**: Debug controls for rapid testing
- **URL parameters**: Direct level loading (e.g., `?level=0&skipMenu=1`)

## Troubleshooting

### Site not updating after push

1. Check the GitHub Actions workflow run completed successfully
2. Wait 1-2 minutes for GitHub Pages to rebuild (separate from the workflow)
3. Hard refresh your browser (Ctrl+Shift+R / Cmd+Shift+R)
4. Check that GitHub Pages is enabled in repository settings

### MIME type errors

The `.nojekyll` file in the deployment prevents Jekyll from interfering with `.js` and `.wasm` files. If you see MIME type errors, ensure this file exists in the `gh-pages` branch.

### Workflow fails to deploy

1. Verify the repository has Actions enabled
2. Check that `GITHUB_TOKEN` has sufficient permissions (should be automatic)
3. Ensure the workflow has `contents: write` and `pages: write` permissions

## Manual Deployment

If you need to deploy manually:

```bash
# Build the site
python3 build.py --wasm

# Create deployment directory
mkdir -p deploy-pages
cp -r build-wasm/Nanosaur.html deploy-pages/game/index.html
cp build-wasm/Nanosaur.{js,wasm,data} deploy-pages/game/
cp docs/index.html deploy-pages/
touch deploy-pages/.nojekyll

# Commit to gh-pages branch
git checkout --orphan gh-pages
git add deploy-pages/*
git commit -m "Manual deployment"
git push origin gh-pages --force
```

## Security Notes

- The site is served over HTTPS automatically by GitHub Pages
- No server-side code or databases are required
- All game logic runs client-side in the browser
- Game data is embedded in the WebAssembly bundle

## Credits

WebAssembly port automation and GitHub Pages deployment by the Nanosaur community.
